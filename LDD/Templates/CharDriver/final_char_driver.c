#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;

static int my_open(struct inode *i, struct file *f)
{
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	return 0;
}

#define MAX_SIZE 1000
static char k_buf[MAX_SIZE];

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: In read\n");

    if (*off + len > MAX_SIZE)
    {
    	printk(KERN_WARNING "In read: Not enough data available\n");
    	return 0;
    }

    if (copy_to_user(buf, k_buf + *off, len))   
    {
	return -EFAULT;
    }
    printk(KERN_INFO "%d bytes read\n", len);
    *off = *off + len;
    return len;

}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: In read\n");
    if (copy_from_user(k_buf, buf, len))
    {
	return -EFAULT;
    }
    printk(KERN_INFO "%d bytes written\n", len);
    return len;
}

static struct file_operations driver_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};

static int __init fcd_init(void)
{
    int ret;
    struct device *dev_ret;

    if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "final_driver")) < 0)
    {
	return ret;
    }

    cdev_init(&c_dev, &driver_fops);

    if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
    {
	unregister_chrdev_region(dev, MINOR_CNT);
	return ret;
    }
    /* create structure class using using class_create */
    if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
    {
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	return PTR_ERR(cl);
    }
    /* Create device file with major , minor specified in dev */
    if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "mychar%d", 0)))
    {
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	return PTR_ERR(dev_ret);
    }

    return 0;
}

static void __exit fcd_exit(void)
{
    device_destroy(cl, dev);
    class_destroy(cl);
    cdev_del(&c_dev);
    unregister_chrdev_region(dev, MINOR_CNT);
}

module_init(fcd_init);
module_exit(fcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech <embedded.courses@emertxe.com>");
MODULE_DESCRIPTION("A Character Driver");
