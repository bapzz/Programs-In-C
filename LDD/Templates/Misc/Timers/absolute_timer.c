#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/proc_fs.h>

/*
 * This file, on the other hand, returns the current time forever
 */
int jit_currentime(char *buf, char **start, off_t offset, int len, int *eof, void *data)
{
	struct timeval tv1;
	struct timespec tv2;
	unsigned long j1;
	u64 j2;

#if 0
	if (offset > 20)
	{
	    return 0;
	}
#endif

	/* get them four */
	j1 = jiffies;
	j2 = get_jiffies_64();
	do_gettimeofday(&tv1);
	tv2 = current_kernel_time();

	/* print */
	len=0;
	len += sprintf(buf,"0x%ld 0x%Ld %d.%d\n %d.%d\n",
		       j1, j2,
		       (int) tv1.tv_sec, (int) tv1.tv_usec,
		       (int) tv2.tv_sec, (int) tv2.tv_nsec);
	*start = buf;
	return len;

}

int __init absolute_time_init(void)
{
	create_proc_read_entry("currentime", 0, NULL, jit_currentime, NULL);
	printk("Hello Universe\n");

	return 0; /* success */
}

void __exit absolute_time_cleanup(void)
{
	remove_proc_entry("currentime", NULL);
	printk("Bye Universe\n");
}

module_init(absolute_time_init);
module_exit(absolute_time_cleanup);

MODULE_DESCRIPTION("kernel Absolute timer drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
