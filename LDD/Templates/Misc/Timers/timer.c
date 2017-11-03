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

static struct timer_list timer_test_1;
 
/*
 * Specify how much msec delay require through insmod
 */
static ulong delay = 10000;
//module_param(delay, ulong, 0);
//MODULE_PARM_DESC(delay, "number of seconds to delay before firing; default = 5 seconds");

static void timer_test_function(unsigned long Delay)
{
	printk("End jiffies : %ld\n", jiffies);
	printk("timer_test_func: with my data '%ld'!\n", Delay);
	del_timer(&timer_test_1);
}

static int __init timer_test_init(void)
{
	printk("Timer init started\n");
	printk("timer 1 to fire %lu seconds from now\n", delay);

	timer_test_1.function = &timer_test_function;
	timer_test_1.data = delay;
	/* n millliseconds */
	//timer_test_1.expires = jiffies + delay * HZ / 1000;
	timer_test_1.expires = jiffies + msecs_to_jiffies(delay);
	/* Adding the timer structure to the Global timer Function */
	init_timer(&timer_test_1);
	/*  Start the timer */
	add_timer(&timer_test_1);
	printk("Start jiffies : %ld\n", jiffies);
	return 0;
}

static void __exit timer_test_cleanup(void)
{
	printk("Cleanup Module\n");
}

module_init(timer_test_init);
module_exit(timer_test_cleanup);

MODULE_DESCRIPTION("kernel timer drive example");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
