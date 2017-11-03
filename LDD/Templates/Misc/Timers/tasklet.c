#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>

#include <linux/time.h>
#include <linux/timer.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/sched.h>

#include <asm/hardirq.h>
#define JIT_ASYNC_LOOPS 5

/* This data structure used as "data" for the timer and tasklet functions */
struct jit_data {
	struct tasklet_struct tlet;
	int hi; /* tasklet or tasklet_hi */
	wait_queue_head_t wait;
	unsigned long prevjiffies;
	unsigned char *buf;
	int loops;
};

void jit_tasklet_fn(unsigned long arg)
{
	struct jit_data *data = (struct jit_data *)arg;
	unsigned long j = jiffies;
	printk("Tasklet function is called\n");
	data->buf += sprintf(data->buf, "%9li  %3li     %i    %6i    %s\n",
			     j, j - data->prevjiffies, in_interrupt() ? 1 : 0,
			     current->pid, current->comm);

	if (--data->loops) 
	{
		data->prevjiffies = j;
		printk("loop : %d\n", data->loops);
		if (data->hi)
			tasklet_hi_schedule(&data->tlet);
		else
			tasklet_schedule(&data->tlet);
	}
	else
	{
		wake_up_interruptible(&data->wait);
		printk("Wakeup interrupted\n");
		tasklet_disable(&data->tlet);
	}
}

int jit_tasklet(char *buf, char **start, off_t offset,
	      int len, int *eof, void *arg)
{
	struct jit_data *data;
	char *buf2 = buf;
	unsigned long j = jiffies;
	long hi = (long)arg;

	printk("Tasklet \n");
	data = kmalloc(sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	init_waitqueue_head(&data->wait);

	/* write the first lines in the buffer */
	buf2 += sprintf(buf2, "   time   delta  inirq    pid   command\n");
	buf2 += sprintf(buf2, "%9li  %3li     %i    %6i     %s\n",
			j, 0L, in_interrupt() ? 1 : 0,
			current->pid, current->comm);

	/* fill the data for our tasklet function */
	data->prevjiffies = j;
	data->buf = buf2;
	data->loops = JIT_ASYNC_LOOPS;
	
	/* register the tasklet */
	printk("Tasklet Initialised\n");
	tasklet_init(&data->tlet, jit_tasklet_fn, (unsigned long)data);
	data->hi = hi;
	if (hi)
	{
		tasklet_hi_schedule(&data->tlet);
		printk("Tasklet Scheduled\n");
	}
	else
		tasklet_schedule(&data->tlet);

	/* wait for the buffer to fill */
	printk("Wait queue enabled\n");
	wait_event_interruptible(data->wait, !data->loops);

	buf2 = data->buf;
	kfree(data);
	printk("Done.......\n");
	return buf2 - buf;
}

int __init jit_init(void)
{
	printk("Hai Universe\n");
	create_proc_read_entry("jitasklet", 0, NULL, jit_tasklet, (void *)1);
	return 0;
}

void __exit jit_cleanup(void)
{
	printk("Bye Universe\n");
	remove_proc_entry("jitasklet", NULL);
}

module_init(jit_init);
module_exit(jit_cleanup);

MODULE_DESCRIPTION("kernel Absolute timer drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
