/* Simple USB driver for Emertxe LDD Kit

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of
  the License, or (at your option) any later version.

  Copyright (C) 2013 by Emertxe
*/

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/completion.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <linux/usb.h>
#include <linux/usb/cdc.h>

/* version information */
#define DRIVER_VERSION "0.1"
#define DRIVER_SHORT   "uctl_usb"
#define DRIVER_AUTHOR  "Emertxe Information Technologies"
#define DRIVER_DESC    "Emertxe LDD Kit driver"

/* minor number for misc USB devices */
#define USB_IDMOUSE_MINOR_BASE 132

/* vendor and device IDs */
#define UCTL_VENDOR_ID 0x03EB /* Atmel: LuFA based firmware */
#define UCTL_PRODUCT_ID 0x2044

/* Macro definitions */
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define UCTL_TIMEOUT (10 * HZ)

#define USB_RT_ACM              (USB_TYPE_CLASS | USB_RECIP_INTERFACE)

/* device ID table */
static const struct usb_device_id uctl_table[] = {
	{USB_DEVICE(UCTL_VENDOR_ID, UCTL_PRODUCT_ID)}, /* Emertxe LDD Kit */
	{}                                    /* terminating null entry          */
};

MODULE_DEVICE_TABLE(usb, uctl_table);
static DEFINE_MUTEX(open_disc_mutex);

/* structure to hold all of our device specific stuff */
struct usb_uctl {

	struct usb_device *udev; /* save off the usb device pointer */
	struct usb_interface *interface; /* the interface for this device */

	unsigned char *bulk_out_buffer; /* the buffer to receive data */
	size_t bulk_out_size; /* the maximum bulk packet size */
	__u8 bulk_out_endpointAddr; /* the address of the bulk in endpoint */

	int open; /* if the port is open or not */
	int present; /* if the device is not disconnected */
	struct mutex lock; /* locks this structure */
	struct usb_cdc_line_coding line;		/* bits, stop, parity */
};

/* local function prototypes */
static ssize_t uctl_write(struct file *file, const char __user *buf, size_t cnt,
				loff_t * ppos);
/*static ssize_t uctl_read(struct file *file, char __user *buffer,
				size_t count, loff_t * ppos);*/

static int uctl_open(struct inode *inode, struct file *file);
static int uctl_release(struct inode *inode, struct file *file);

static int uctl_probe(struct usb_interface *interface,
				const struct usb_device_id *id);

static void uctl_disconnect(struct usb_interface *interface);

/* file operation pointers */
static const struct file_operations uctl_fops = {
	.owner = THIS_MODULE,
	//.read = uctl_read,
	.write = uctl_write,
	.open = uctl_open,
	.release = uctl_release,
};

/* class driver information */
static struct usb_class_driver uctl_class = {
	.name = "uctl%d",
	.fops = &uctl_fops,
	.minor_base = USB_IDMOUSE_MINOR_BASE,
};

/* usb specific object needed to register this driver with the usb subsystem */
static struct usb_driver uctl_driver = {
	.name = DRIVER_SHORT,
	.probe = uctl_probe,
	.disconnect = uctl_disconnect,
	.id_table = uctl_table, //Device ID
};

/*
 * Functions for ACM control messages.
 */

static int acm_ctrl_msg(struct usb_uctl *acm, int request, int value,
							void *buf, int len)
{
	int retval = usb_control_msg(acm->udev, usb_sndctrlpipe(acm->udev, 0),
		request, USB_RT_ACM, value,
		0,
		buf, len, 5000);
	printk("acm_control_msg: rq: 0x%02x val: %#x len: %#x result: %d",
						request, value, len, retval);
	return retval < 0 ? retval : 0;
}

/* devices aren't required to support these requests.
 * the cdc acm descriptor tells whether they do...
 */
#define acm_set_control(acm, control) \
	acm_ctrl_msg(acm, USB_CDC_REQ_SET_CONTROL_LINE_STATE, control, NULL, 0)
#define acm_set_line(acm, line) \
	acm_ctrl_msg(acm, USB_CDC_REQ_SET_LINE_CODING, 0, line, sizeof *(line))
#define acm_send_break(acm, ms) \
	acm_ctrl_msg(acm, USB_CDC_REQ_SEND_BREAK, ms, NULL, 0)

static inline void uctl_delete(struct usb_uctl *dev)
{
	kfree(dev->bulk_out_buffer);
	kfree(dev);
}

static int uctl_open(struct inode *inode, struct file *file)
{
	struct usb_uctl *dev;
	struct usb_interface *interface;
	int result = 0;

	/* get the interface from minor number and driver information */
	interface = usb_find_interface (&uctl_driver, iminor (inode));
	if (!interface)
		return -ENODEV;

	mutex_lock(&open_disc_mutex);
	/* get the device information block from the interface */
	dev = usb_get_intfdata(interface);
	if (!dev) {
		mutex_unlock(&open_disc_mutex);
		return -ENODEV;
	}

	/* lock this device */
	mutex_lock(&dev->lock);
	mutex_unlock(&open_disc_mutex);

	/* check if already open */
	if (dev->open) {

		/* already open, so fail */
		result = -EBUSY;

	} else {

#if 0
		result = usb_autopm_get_interface(interface);
		if (result)
			goto printkor;
		usb_autopm_put_interface(interface);
#endif

		/* increment our usage count for the driver */
		++dev->open;

		/* save our object in the file's private structure */
		file->private_data = dev;

	} 

printkor:

	/* unlock this device */
	mutex_unlock(&dev->lock);
	return result;
}

static int uctl_release(struct inode *inode, struct file *file)
{
	struct usb_uctl *dev;

	dev = file->private_data;

	if (dev == NULL)
		return -ENODEV;

	mutex_lock(&open_disc_mutex);
	/* lock our device */
	mutex_lock(&dev->lock);

	/* are we really open? */
	if (dev->open <= 0) {
		mutex_unlock(&dev->lock);
		mutex_unlock(&open_disc_mutex);
		return -ENODEV;
	}

	--dev->open;

	if (!dev->present) {
		/* the device was unplugged before the file was released */
		mutex_unlock(&dev->lock);
		mutex_unlock(&open_disc_mutex);
		uctl_delete(dev);
	} else {
		mutex_unlock(&dev->lock);
		mutex_unlock(&open_disc_mutex);
	}
	return 0;
}

static ssize_t uctl_write(struct file *file, const char __user *buf, size_t cnt,
				loff_t * ppos)
{
	struct usb_uctl *dev = file->private_data;
	int wrote_cnt, wrote_size, write_size;
	int result = 0;
	int request = USB_CDC_REQ_SET_CONTROL_LINE_STATE;
	int value = 0x03;
	int index = 0;
	struct usb_cdc_line_coding newline;

	/* lock this object */
	mutex_lock(&dev->lock);

	/* verify that the device wasn't unplugged */
	if (!dev->present) {
		mutex_unlock(&dev->lock);
		return -ENODEV;
	}
	/* Write data to USB Bulk Endpoint */
	wrote_cnt = 0;
	while (wrote_cnt < cnt)
	{
		write_size = MIN(dev->bulk_out_size, cnt - wrote_cnt /* Remaining */);
		/* Using buf may cause sync issues */
		if ((result = copy_from_user(dev->bulk_out_buffer, buf + wrote_cnt, write_size)))
		{
			printk("UCTL: copy_from_user failed\n");
			break;
		}

/* Send USB Control message to enable transfer */
#if 1
		result = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			request, USB_RT_ACM, value, index, NULL, 0, UCTL_TIMEOUT);	
		if (result < 0)
		{
			printk("UCTL: Control message returned %d\n", result);
			break;
		}
		newline.dwDTERate = cpu_to_le32(9600);
		newline.bCharFormat = 0; /* Stop bits - 1 */
		newline.bParityType = 0; /* None */
		newline.bDataBits = 8;

		acm_set_line(dev, &newline);

#endif

		/* Send the data out the bulk port */
		printk(KERN_DEBUG "UCTL: Sending msg '%s' (%d bytes) into %X EP\n", dev->bulk_out_buffer, write_size, dev->bulk_out_endpointAddr);
		result = usb_bulk_msg(dev->udev, usb_sndbulkpipe(dev->udev, dev->bulk_out_endpointAddr),
			dev->bulk_out_buffer, write_size, &wrote_size, UCTL_TIMEOUT);
		if (result < 0)
		{
			printk("Bulk message returned %d\n", result);
			break;
		}
		if (signal_pending(current)) {
			result = -EINTR;
			break;
		}
		wrote_cnt += wrote_size;
		printk("Wrote %d bytes\n", wrote_size);
		/* Disable again */
		result = usb_control_msg(dev->udev, usb_sndctrlpipe(dev->udev, 0),
			request, USB_RT_ACM, 0, index, NULL, 0, UCTL_TIMEOUT);	
		if (result < 0)
		{
			printk("UCTL: Control message returned %d\n", result);
			break;
		}
	}

	/* unlock the device */
	mutex_unlock(&dev->lock);
	return wrote_cnt ? wrote_cnt : result;

}


static int uctl_probe(struct usb_interface *interface,
				const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct usb_uctl *dev;
	struct usb_host_interface *iface_desc;
	struct usb_endpoint_descriptor *endpoint;
	int result;

	printk(KERN_DEBUG "uctl: In Probe\n");
	/* check if we have gotten the data or the hid interface */
	iface_desc = &interface->altsetting[0];
	if (iface_desc->desc.bInterfaceClass != 0x0A)
	{
	    printk(KERN_DEBUG "uctl: We do not support non data (0x0A) i/f\n");
	    return -ENODEV;
	}
	printk(KERN_DEBUG "uctl: Found data (0x0A) i/f\n");

	/* allocate memory for our device state and initialize it */
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (dev == NULL)
		return -ENOMEM;

	mutex_init(&dev->lock);
	dev->udev = udev;
	dev->interface = interface;

	/* set up the endpoint information - use only the first bulk-out endpoint */
	endpoint = &iface_desc->endpoint[0].desc;
	if (!dev->bulk_out_endpointAddr && usb_endpoint_is_bulk_out(endpoint)) {
		/* we found a bulk out endpoint */
		dev->bulk_out_size = le16_to_cpu(endpoint->wMaxPacketSize);
		dev->bulk_out_endpointAddr = endpoint->bEndpointAddress;
		dev->bulk_out_buffer =
			kmalloc(dev->bulk_out_size, GFP_KERNEL);

		if (!dev->bulk_out_buffer) {
			printk("Unable to allocate input buffer.");
			uctl_delete(dev);
			return -ENOMEM;
		}
	}

	if (!(dev->bulk_out_endpointAddr)) {
		printk("Unable to find bulk-in endpoint.");
		uctl_delete(dev);
		return -ENODEV;
	}
	/* allow device read, write and ioctl */
	dev->present = 1;

	/* we can register the device now, as it is ready */
	usb_set_intfdata(interface, dev);
	result = usb_register_dev(interface, &uctl_class);
	if (result) {
		/* something prevented us from registering this device */
		printk("Unble to allocate minor number.");
		usb_set_intfdata(interface, NULL);
		uctl_delete(dev);
		return result;
	}

	/* be noisy */
	dev_info(&interface->dev,"%s now attached\n",DRIVER_DESC);

	return 0;
}

static void uctl_disconnect(struct usb_interface *interface)
{
	struct usb_uctl *dev;

	/* get device structure */
	dev = usb_get_intfdata(interface);

	/* give back our minor */
	usb_deregister_dev(interface, &uctl_class);

	mutex_lock(&open_disc_mutex);
	usb_set_intfdata(interface, NULL);
	/* lock the device */
	mutex_lock(&dev->lock);
	mutex_unlock(&open_disc_mutex);

	/* prevent device read, write and ioctl */
	dev->present = 0;

	/* if the device is opened, uctl_release will clean this up */
	if (!dev->open) {
		mutex_unlock(&dev->lock);
		uctl_delete(dev);
	} else {
		/* unlock */
		mutex_unlock(&dev->lock);
	}

	dev_info(&interface->dev, "disconnected\n");
}

static int __init usb_uctl_init(void)
{
	int result;

	printk(KERN_INFO KBUILD_MODNAME ": " DRIVER_VERSION ":"
	       DRIVER_DESC "\n");

	/* register this driver with the USB subsystem */
	result = usb_register(&uctl_driver);
	if (result)
		printk("Unable to register device (printkor %d).", result);

	return result;
}

static void __exit usb_uctl_exit(void)
{
	/* deregister this driver with the USB subsystem */
	usb_deregister(&uctl_driver);
}

module_init(usb_uctl_init);
module_exit(usb_uctl_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
