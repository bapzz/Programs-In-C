#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/errno.h>
#include <asm/atomic.h>
#include <asm/bitops.h>

int __init init_module()
{
	atomic_t v;
	unsigned int bit = 1;
	unsigned long data = 0;
	int j = 0;

	printk("Hai Univarse\n");

	atomic_set(&v, 10);
	j = atomic_read(&v);
	printk("atomic Read : %d\n", j);

	atomic_add(j, &v);
	j = atomic_read(&v);
	printk("atomic add : %d\n", j);

	atomic_sub(j, &v);
	j = atomic_read(&v);
	printk("atomic sub : %d\n", j);

	atomic_inc(&v);
	j = atomic_read(&v);
	printk("atomic inc : %d\n", j);

	atomic_dec(&v);
	j = atomic_read(&v);
	printk("atomic dec : %d\n", j);

	printk("The Present Data:\n");
	printk("Bit : %d Data : %ld\n", bit, data);

	set_bit(bit, &data);
	printk("data = %ld\n", data);
	clear_bit(bit, &data);
	printk("data = %ld\n", data);
	change_bit(bit, &data);
	printk("data = %ld\n", data);

	return 0;
}

void __exit cleanup_module()
{
	printk("Bye Universe\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mubeen");
MODULE_DESCRIPTION("A Character Driver");
