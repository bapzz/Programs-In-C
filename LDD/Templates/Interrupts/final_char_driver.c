#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>	/* We want an interrupt */
#include <linux/sched.h>
#include <linux/semaphore.h>

#define FIRST_MINOR 0
#define MINOR_CNT 1
#define IRQ_NUMBER 1

struct tasklet_struct tlet;
struct semaphore sem;
unsigned char scan_code;

static dev_t dev;
static struct cdev c_dev;
static struct class *cl;

int start_reading;

void get_scan_code(unsigned long arg)
{
    unsigned char status;

    status = inb(0x64);
    scan_code = inb(0x60);

    printk("Scan code %X (%s)\n", scan_code & 0x7F, (scan_code & 0x80) ? "Released" : "Pressed");

    if (start_reading == 1)
    {
	start_reading = 0;
	up(&sem);
    }
}

/* This function services keyboard interrupt.  */
irqreturn_t irq_handler(int irq, void *dev_id)
{
	tasklet_hi_schedule(&tlet);
	//get_scan_code(1L);
	return IRQ_HANDLED;
}
static int my_open(struct inode *i, struct file *f)
{
	return 0;
}
static int my_close(struct inode *i, struct file *f)
{
	return 0;
}

#define MAX_SIZE 1000
static char k_buf[MAX_SIZE];

static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: In read\n");

    start_reading = 1;
    down(&sem);

    if (copy_to_user(buf, &scan_code, 1))   
    {
	return -EFAULT;
    }
    return 1;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "Driver: In read\n");
    if (copy_from_user(k_buf, buf, len))
    {
	return -EFAULT;
    }
    printk(KERN_INFO "%d bytes written\n", len);
    return len;
}

static struct file_operations driver_fops =
{
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    //.write = my_write
};

static int __init fcd_init(void)
{
    int ret, error = 0;
    struct device *dev_ret;

    if ((ret = alloc_chrdev_region(&dev, FIRST_MINOR, MINOR_CNT, "final_driver")) < 0)
    {
	return ret;
    }

    cdev_init(&c_dev, &driver_fops);

    if ((ret = cdev_add(&c_dev, dev, MINOR_CNT)) < 0)
    {
	unregister_chrdev_region(dev, MINOR_CNT);
	return ret;
    }

    if (IS_ERR(cl = class_create(THIS_MODULE, "char")))
    {
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	return PTR_ERR(cl);
    }
    if (IS_ERR(dev_ret = device_create(cl, NULL, dev, NULL, "mykeyboard%d", 0)))
    {
	class_destroy(cl);
	cdev_del(&c_dev);
	unregister_chrdev_region(dev, MINOR_CNT);
	return PTR_ERR(dev_ret);
    }
    /* Registering ISR for Keyboard (IRQ1) */
    error = request_irq(IRQ_NUMBER, &irq_handler, IRQF_SHARED, "keyboard2", &dev);

    if(error)
    {
	printk("Mubeen: Error no = %d\n", error);
	return error;
    }
    else
    {
	printk("Mubeen: Registerd driver\n");
    }
    tasklet_init(&tlet, get_scan_code, 1L);
    sema_init(&sem, 0);

    return 0;
}

static void __exit fcd_exit(void)
{
    /* 
     * Freeing our KB interrupt handler
     */
    tasklet_kill(&tlet);
    free_irq(IRQ_NUMBER, &dev);

    device_destroy(cl, dev);
    class_destroy(cl);
    cdev_del(&c_dev);
    unregister_chrdev_region(dev, MINOR_CNT);
}

module_init(fcd_init);
module_exit(fcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Emertxe Info Tech <embedded.courses@emertxe.com>");
MODULE_DESCRIPTION("A Character Driver");
