#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/time.h>
#include <linux/proc_fs.h>
#include <linux/moduleparam.h>
#include <asm/uaccess.h>

/*
 * Specify how much msec delay require through insmod
 */
static ulong delay = 30;
module_param(delay, ulong, 0);
MODULE_PARM_DESC(delay, "number of seconds to delay before firing; default = 5 seconds");

int jit_fn(char *buf, char **start, off_t offset, int len, int *eof, void *data)
{
	unsigned long j0, j1; /* jiffies */

	j0 = jiffies;
	j1 = j0 + delay;

	while (time_before(jiffies, j1))
	{
		printk("j0:%ld j1:%ld jiffies:%ld\n", j0, j1, jiffies);
		cpu_relax();
	}
	j1 = jiffies; /* actual value after we delayed */

	len = sprintf(buf, "%ld %ld\n", j0, j1);
	*start = buf;
	return len;
}

int __init busy_init(void)
{
	printk("Hello Unniverse\n");
	create_proc_read_entry("jitbusy", 0, NULL, jit_fn, NULL);
	return 0;
}

void __exit busy_cleanup(void)
{
	remove_proc_entry("jitbusy", NULL);
	printk("Bye Unniverse\n");
}

module_init(busy_init);
module_exit(busy_cleanup);

MODULE_DESCRIPTION("kernel Busy Waiting drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
