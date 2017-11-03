#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/interrupt.h>

#define LIMIT	(PAGE_SIZE-128)	/* don't print any more after this size */

static struct work_struct jiq_work;
static int jiq_print(void);
static void *jiq_print_wq(void);
/*
 * The delay for the delayed workqueue timer file.
 */
static unsigned long Delay = 1;
module_param(Delay, long, 0);


static struct clientdata
{
	int len;
	char *buf;
	unsigned long jiffies;
	unsigned long delay;
} jiq_data;

/*
 * Do the printing; return non-zero if the task should be rescheduled.
 */
static int jiq_print()
{
	int len = jiq_data.len;
	char *buf = jiq_data.buf;
	unsigned long j = jiffies;

	if (len > LIMIT) 
	{ 
		printk("No Memory\n");
		return 0;
	}

	if (len == 0)
	{
		len = sprintf(buf,"    time    delta   preempt  pid  cpu command\n");
	}
	else
	{
		len =0;
	}

	len += sprintf(buf+len, "%9li  %4li     %3i %5i %3i %s\n",
			j, j - jiq_data.jiffies,
			preempt_count(), current->pid, smp_processor_id(),
			current->comm);

	jiq_data.len += len;
	jiq_data.buf += len;
	jiq_data.jiffies = j;
//	jiq_data.delay = Delay;
	return 1;
}

/*
 * Call jiq_print from a work queue
 */
static void *jiq_print_wq(void)
{
	if (! jiq_print ())
	{
		return &Delay;
	}

	if (jiq_data.delay)
	{
		printk("Inside the schedule_delayed_work\n");
		flush_scheduled_work();
	}
	else
	{
		printk("Inside the schedule_work\n");
		/*
		 * put work task in global workqueue
		 * This puts a job in the kernel-global workqueue.
		 * 	So you have a work queue data structure and a work queue handler—how do you schedule it to run?
		 * 		To queue a given work queue handler to run at the kernel's earliest possible convenience,
		 * 		invoke the following function, passing it your work queue structure
		 * 	This function returns nonzero if the work was successfully queued; on error, it returns zero.
		 * 		The function can be called from either process or interrupt context.
		 */
		if (schedule_work(&jiq_work) != 0)
		{
			printk("Successfully\n");
		}
		else
		{
			printk("Fail\n");
			return 0;
		}
	}
		return &Delay;
}

static int jiq_read_wq(char *buf, char **start, off_t offset, int len, int *eof, void *data)
{
    printk("Called read: jiq_read_wq\n");
	jiq_data.len = 0;                /* nothing printed, yet */
	jiq_data.buf = buf;              /* print in this place */
	jiq_data.jiffies = jiffies;      /* initial time */
	jiq_data.delay = 0;
    
		if (schedule_work(&jiq_work) != 0)
		{
			schedule();
		}
		else
		{
			return 0;
		}

	*eof = 1;
	return jiq_data.len;
}

/*
 * init function
 */
static int jiq_init(void)
{
	printk("Hello Universe\n");
	/* this line is in jiq_init() */
	INIT_WORK(&jiq_work, (void *)jiq_print_wq);

	create_proc_read_entry("jiq_read_wq", 0, NULL, jiq_read_wq, NULL);

	return 0; /* succeed */
}

/*
 * Clean-up function
 */
static void jiq_cleanup(void)
{
	printk("Bye Universe\n");
	remove_proc_entry("jiq_read_wq", NULL);
}


module_init(jiq_init);
module_exit(jiq_cleanup);

MODULE_DESCRIPTION("kernel Work Queue's drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
