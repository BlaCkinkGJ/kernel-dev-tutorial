#include <linux/blkdev.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

static int __init ramdisk_init(void)
{
	int ret = 0;
	printk(KERN_INFO "hello world\n");
	return ret;
}

static void __exit ramdisk_exit(void)
{
	printk(KERN_INFO "bye bye!!\n");
}

module_init(ramdisk_init);
module_exit(ramdisk_exit);

MODULE_AUTHOR("BlaCkinkGJ");
MODULE_LICENSE("GPL");
