/*
 * Creating New Worker Threads
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

/*
 * In rare cases, the default worker threads may be insufficient.
 * Thankfully, the work queue interface allows you to create your own worker threads 
 * And use those to schedule your bottom-half work.
 * To create new worker threads, invoke the function:
 */
static struct workqueue_struct *single_work_queue;

#if 0
#define FIRST_MINOR 0
#define MINOR_CNT 1

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;
static char *Data;

/*
 * In rare cases, the default worker threads may be insufficient.
 * Thankfully, the work queue interface allows you to create your own worker threads 
 * And use those to schedule your bottom-half work.
 * To create new worker threads, invoke the function:
 */
static struct workqueue_struct *single_work_queue;

static int my_open(struct inode *i, struct file *f)
{
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	return 0;
}

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
	if (*off == 0)
	{
		Data = kmalloc(len , GFP_KERNEL);

		/*
		 * Checking is this a bogus pointer
		 */
		if (IS_ERR(Data))
		{
			printk("Failed to allocate Memory");
			return -ENOMEM;
		}

		for (i = 0; i < len; i++)
		{
			if (copy_from_user((Data + i), (buf + i), 1))
			{
				kfree(Data);
				return -EFAULT;
			}				
		}
		*(Data + len) = '\0';
		*off += 1;
		return len;
	}
	else
	{
		return 0;
	}
}

static struct file_operations anil_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};
#endif


static int my_own_thread_init()
{
	printk("Hello Unniverse\n");

	/* create a new single worker thread */
	single_work_queue = create_singlethread_workqueue("My_Thread");

	return 0;
}

static void my_own_thread_exit()
{
	flush_workqueue(single_work_queue);
	/* Destroy a worker thread*/
	destroy_workqueue(single_work_queue);
}

module_init(my_own_thread_init);
module_exit(my_own_thread_exit);
