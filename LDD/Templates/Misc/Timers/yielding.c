#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>

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
		schedule();
	}
	j1 = jiffies; /* actual value after we delayed */

	len = sprintf(buf, "%ld %ld\n", j0, j1);
	*start = buf;
	return len;
}

int __init yielding_init(void)
{
	printk("Hello Unniverse\n");
	create_proc_read_entry("jityielding", 0, NULL, jit_fn, NULL);
	return 0;
}

void __exit yielding_cleanup(void)
{
	remove_proc_entry("jityielding", NULL);
	printk("Bye Unniverse\n");
}

module_init(yielding_init);
module_exit(yielding_cleanup);

MODULE_DESCRIPTION("kernel Yielding Delays drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
