/*
 * Creating New Worker Threads
 * But is it the right bottom half for you? 
 * 		If you need to run your bottom half in process context, a work queue is your only option.
 * 		Furthermore, if you are considering creating a kernel thread, a work queue may be a better choice
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/moduleparam.h>

#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/workqueue.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>

#include <linux/spinlock.h>
#include <linux/slab.h>

#define LIMIT	(PAGE_SIZE - 128)	/* don't print any more after this size */

/*
 * Your work queue handler runs in process context, it can sleep if needed.
 */
static void *my_work_queue_fn(void);
static int print(void);

/*
 * In rare cases, the default worker threads may be insufficient.
 * Thankfully, the work queue interface allows you to create your own worker threads 
 * And use those to schedule your bottom-half work.
 * To create new worker threads, invoke the function:
 */
static struct workqueue_struct *single_work_queue;
static struct work_struct my_workqueue;

static ulong delay = 30;
module_param(delay, ulong, 0);

static struct clientdata
{
	int len;
	char *buf;
	unsigned long jiffies;
	unsigned long delay;
	spinlock_t my_lock;
}jiq_data;

static int print()
{
	int len = jiq_data.len;
	char *buf = jiq_data.buf;
	unsigned long j = jiffies;

	spin_lock(&jiq_data.my_lock);
	if (len > LIMIT) 
	{ 
		printk("No Memory\n");
		spin_unlock(&jiq_data.my_lock);
		return 0;
	}

	if (len == 0)
	{
		len = sprintf(buf,"time       delta    preempt   pid    cpu   command\n");
	}
	else
	{
		len =0;
	}

	len += sprintf(buf+len, "%9li    %4li     %3i  %5i  %3i  %s\n",
			j, j - jiq_data.jiffies,
			preempt_count(), current->pid, smp_processor_id(),
			current->comm);

	printk("%s\n", buf);
	jiq_data.len += len;
	jiq_data.buf += len;
	jiq_data.jiffies = j;
	jiq_data.delay = delay;
	spin_unlock(&jiq_data.my_lock);

	return 1;
}

static void *my_work_queue_fn(void)
{
	if (!print())
	{
		return &delay;
	}

	if (jiq_data.delay)
	{
		printk("Inside the schedule_delayed_work\n");
		/*
		 * Finally, you may flush a specific work queue with the function
		 * This function waits until all queued work on the work queue has completed before returning
		 */
		flush_workqueue(single_work_queue);
	}
	else
	{
		printk("Inside the schedule_work\n");
		/*
		 * put work task in global workqueue
		 * This puts a job in the kernel-global workqueue.
		 */
	}
	return &delay;
}

int jit_work_queue(char *buf, char **start, off_t offset, int len, int *eof, void *data)
{
	wait_queue_head_t wait;

	init_waitqueue_head (&wait);

	jiq_data.len = 0;                /* nothing printed, yet */
	jiq_data.buf = buf;              /* print in this place */
	jiq_data.jiffies = jiffies;      /* initial time */
	jiq_data.delay = 0;
	/*
	 * sleep until a condition gets true or a timeout elapses
	 * This doesnt go on forever
	 */
	printk("Sleeping started @ %ld\n", (jiq_data.jiffies = jiffies));
	wait_event_interruptible_timeout(wait, 0, delay);
	printk("Sleeping End     @ %ld\n", (jiq_data.jiffies - delay));

	/*
	 * Here, single_work_queue is a pointer to the specific work queue that you created using the call to create_workqueue(),
	 * and is a my_workqueue pointer to your work queue structure
	 *
	 * These functions are analogous to schedule_work()
	 * Except they queue the given work into the given work queue instead of the default one.
	 * These functions return nonzero on success and zero on failure
	 * These functions may be called from both interrupt and process context.
	 */
	if(!jiq_data.delay)
	{
		printk("Putting the Work in Queue\n");
		queue_work(single_work_queue, &my_workqueue);
		schedule();
	}
	else
	{
		printk("No Time To Schedule\n");
	}

	return len;
}


static int __init my_own_thread_init(void)
{
	printk("Hello Unniverse\n");
	create_proc_read_entry("jit_work_queue", 0, NULL, jit_work_queue, NULL);

	memset(&jiq_data, 0, sizeof(jiq_data));

	/* In rare cases, the default worker threads may be insufficient.
	 * Thankfully, the work queue interface allows you to create your own worker threads and 
	 * use those to schedule your bottom-half work.
	 * To create a new single worker thread
	 */
	single_work_queue = create_singlethread_workqueue("My_Thread");
	if(single_work_queue == NULL)
	{
		return -1;
	}

	spin_lock_init(&jiq_data.my_lock);

	INIT_WORK(&my_workqueue, (void *)my_work_queue_fn);

	return 0;
}

static void __exit my_own_thread_exit(void)
{
	printk("Bye Unniverse\n");
	remove_proc_entry("jit_work_queue", NULL);

	/*
	 * Wait on all pending work on the given worker thread
	 */
	flush_workqueue(single_work_queue);

	/* 
	 * Destroy a worker thread
	 */
	destroy_workqueue(single_work_queue);
}

module_init(my_own_thread_init);
module_exit(my_own_thread_exit);

MODULE_DESCRIPTION("kernel Wait Queue's drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
