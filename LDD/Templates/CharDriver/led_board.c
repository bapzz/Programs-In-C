#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/serial_reg.h>
#include <asm/io.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

#define SERIAL_PORT 0x3F8

static int my_open(struct inode *i, struct file *f)
{
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	return 0;
}

static void led_on(void)
{
	char bitstate;

	bitstate = inb(SERIAL_PORT + UART_MCR ); // Read current MCR value
	bitstate |= UART_MCR_RTS; // Data = 1
	bitstate |= UART_MCR_DTR; // Clock = 1
	outb(bitstate, SERIAL_PORT + UART_MCR ); // Write new value to MCR
	msleep(10); // Sleep for CLK pulse (high)
	bitstate = inb(SERIAL_PORT + UART_MCR ); // Read MCR value again
	bitstate &= ~UART_MCR_DTR; // Clock = 0
	outb(bitstate, SERIAL_PORT + UART_MCR ); // Write new value to MCR
	msleep(10);
}

static void led_off(void)
{
	char bitstate;

	bitstate = inb(SERIAL_PORT + UART_MCR );
	bitstate &= ~UART_MCR_RTS; // Data = 0
	bitstate |= UART_MCR_DTR;
	outb(bitstate, SERIAL_PORT + UART_MCR );
	msleep(10);
	bitstate = inb(SERIAL_PORT + UART_MCR );
	bitstate &= ~UART_MCR_DTR;
	outb(bitstate, SERIAL_PORT + UART_MCR );
	msleep(10);
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t cnt, loff_t *off)
{
	int i, j;
	unsigned char val;

	/* For each character */
	for (i = 0; i < cnt; i++)
	{
		if (copy_from_user(&val, buf + i, 1))
		{
			return -EFAULT;
		}	
		/* For each bit */
		for (j = 0; j < 8; j++)
		{
			if (val & (0x80 >> j))
			{
				led_on();
			}
			else
			{
				led_off();
			}
		}
		msleep(1000);
	}

	return cnt;
}

static dev_t dev;
static struct file_operations my_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.write = my_write
};
static struct cdev c_dev;
static struct class *cl;

static int __init led_board_init(void)
{
	int ret;
	struct device *dev_ret;

	if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "led_board")) < 0)
	{
		return ret;
	}

	cdev_init(&c_dev, &my_fops);
	if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
	{
		unregister_chrdev_region(dev, MINOR_CNT);
		return ret;
	}

	if (IS_ERR(cl = class_create(THIS_MODULE, "led")))
	{
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(cl);
	}

	if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "led%d", 0)))
	{
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return PTR_ERR(dev_ret);
	}

	return 0;
}

static void __exit led_board_exit(void)
{
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
}

module_init(led_board_init);
module_exit(led_board_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech <embedded.courses@emertxe.com>");
MODULE_DESCRIPTION("LED Array Driver for DDK v1.1");
