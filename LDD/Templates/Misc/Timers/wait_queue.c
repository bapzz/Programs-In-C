#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/moduleparam.h>
#include <linux/wait.h>
#include <linux/sched.h>

static ulong delay = 30;
module_param(delay, ulong, 0);
MODULE_PARM_DESC(delay, "number of seconds to delay before firing; default = 5 seconds");

int jit_fn(char *buf, char **start, off_t offset, int len, int *eof, void *data)
{
	unsigned long j0, j1; /* jiffies */
	wait_queue_head_t wait;

	init_waitqueue_head (&wait);
	j0 = jiffies;

	/*
	 * sleep until a condition gets true or a timeout elapses
	 * This doesnt go on forever
	 */
	printk("Sleeping started @ %ld\n", jiffies);
	wait_event_interruptible_timeout(wait, 0, delay);
	printk("Sleeping End     @ %ld\n", (jiffies - delay));
	j1 = jiffies; /* actual value after we delayed */

	len = sprintf(buf, "previous : %ld expire : %ld diff(%ld)\n", j0, j1, (j1 - j0));
	*start = buf;
	return len;
}

int __init wait_queue_init(void)
{
	printk("Hello Unniverse\n");
	create_proc_read_entry("jitwait", 0, NULL, jit_fn, NULL);
	return 0;
}

void __exit wait_queue_cleanup(void)
{
	remove_proc_entry("jitwait", NULL);
	printk("Bye Unniverse\n");
}

module_init(wait_queue_init);
module_exit(wait_queue_cleanup);

MODULE_DESCRIPTION("kernel Wait Queue's drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
