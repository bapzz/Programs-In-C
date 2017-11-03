#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/sched.h>  /* current and everything */
#include <linux/types.h>  /* size_t */
#include <linux/wait.h>
#include <asm/uaccess.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;


static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag = 0;

static int sleepy_open(struct inode *i, struct file *f)
{
	return 0;
}
static int sleepy_close(struct inode *i, struct file *f)
{
	return 0;
}

ssize_t sleepy_read (struct file *filp, char __user *buf, size_t count, loff_t *pos)
{
	printk(KERN_DEBUG "process %i (%s) going to sleep\n",
			current->pid, current->comm);
	wait_event_interruptible(wq, flag != 0);
	flag = 0;
	printk(KERN_DEBUG "awoken %i (%s)\n", current->pid, current->comm);
	return 0; /* EOF */
}

ssize_t sleepy_write (struct file *filp, const char __user *buf, size_t count,
		loff_t *pos)
{
	printk(KERN_DEBUG "process %i (%s) awakening the readers...\n",
			current->pid, current->comm);
	flag = 1;
	wake_up_interruptible(&wq);
	return count; /* succeed, to avoid retrial */
}


struct file_operations sleepy_fops = {
	.owner = THIS_MODULE,
	.open = sleepy_open,
	.release = sleepy_close,
	.read =  sleepy_read,
	.write = sleepy_write,
};


int sleepy_init(void)
{
	printk("Hello Universe\n");
	if (alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "EMX") < 0)
	{
		return -1;
	}
	printk("Major Nr: %d\n", MAJOR(dev));

	cdev_init(&c_dev, &sleepy_fops);

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

	return 0;
}

void sleepy_cleanup(void)
{
	device_destroy(cl, dev);
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	printk("Bye Universe\n");

}

module_init(sleepy_init);
module_exit(sleepy_cleanup);
MODULE_LICENSE("Dual BSD/GPL");
