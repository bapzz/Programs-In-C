#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <asm/uaccess.h>
#include <linux/timer.h>

static unsigned long delay = 10;
static unsigned long data = 10;

static struct timer_list timer_structure;

static void timer_test_function(unsigned long Delay)
{
	int ret;
	printk("In jiffies : %ld\n", jiffies);
	printk("timer_test_func: with my data '%ld'!\n", Delay);
	ret = mod_timer(&timer_structure, (jiffies + msecs_to_jiffies(delay * 2 * 1000)));
	printk("jiffies : %ld\n", jiffies);
	if(ret)
	{
		printk("mod_timer failed\n");
	}
}

static int __init timer_test_init(void)
{
	int ret;
	printk("Timer init started\n");
	/*
	 * This function fills the timer list structure & calls the init_timer function
	 */
	setup_timer(&timer_structure, timer_test_function, data);
	printk("Before jiffies : %ld\n", jiffies);
	ret = mod_timer(&timer_structure, (jiffies + msecs_to_jiffies(delay * 2 * 1000)));
	printk("After jiffies : %ld\n", jiffies);
	if(ret)
	{
		printk("mod_timer failed\n");
		return ret;
	}

	return 0;
}

static void __exit timer_test_cleanup(void)
{
	printk("Cleanup Module\n");
	del_timer(&timer_structure);
}

module_init(timer_test_init);
module_exit(timer_test_cleanup);

MODULE_DESCRIPTION("kernel timer drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
