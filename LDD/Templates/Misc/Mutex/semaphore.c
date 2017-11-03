#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;
static struct semaphore my_semaphore;
static int count = 2;

static int my_open(struct inode *i, struct file *f)
{
	printk("count 			: %d\n", count);
	printk("semaphore-count : %d\n", my_semaphore.count);
	down(&my_semaphore);
	printk("semaphore-count : %d\n", my_semaphore.count);
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	up(&my_semaphore);
	return 0;
}

static char c = 'A';

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
	if (*off == 0)
	{
		if (copy_to_user(buf, &c, 1))
		{
			return -EFAULT;
		}
		*off += 1;
		return 1;
	}
	else
		return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
	if (copy_from_user(&c, buf + len - 1, 1))
	{
		return -EFAULT;
	}
	return len;
}

static struct file_operations sri_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};

int __init init_module()
{
	printk("Hello Universe\n");
	if (alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "EMX") < 0)
	{
		return -1;
	}
	printk("Major Nr: %d\n", MAJOR(dev));

	cdev_init(&c_dev, &sri_fops);

	if (cdev_add(&c_dev, dev, MINOR_CNT) == -1)
	{
		unregister_chrdev_region(dev, MINOR_CNT);
		return -1;
	}
	
	if ((cl = class_create(THIS_MODULE, "chardrv")) == NULL)
	{
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return -1;
	}
	if (device_create(cl, NULL, dev, NULL, "mychar%d", 0) == NULL)
	{
		class_destroy(cl);
		cdev_del(&c_dev);
		unregister_chrdev_region(dev, MINOR_CNT);
		return -1;
	}
	sema_init(&my_semaphore, count);

	return 0;
}

void __exit cleanup_module()
{
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	printk("Bye Universe\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
MODULE_DESCRIPTION("A Character Driver");
