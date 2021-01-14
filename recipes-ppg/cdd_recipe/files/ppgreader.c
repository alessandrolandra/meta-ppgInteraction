#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>

#include "data.h"

static dev_t ppgreader_dev;
struct cdev ppgreader_cdev;
struct class *myclass = NULL;
static char buffer[64];

ssize_t ppgreader_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{	
	static int i=0;
	sprintf(buf,"%d",ppg[i]);
	i=(i+1)%2048;
	return 1;
}
ssize_t ppgreader_release(struct inode *inodep, struct file *filp)
{
	printk(KERN_INFO "[ppgreader] release\n");
	return 0;
}

struct file_operations ppgreader_fops = {
	.owner = THIS_MODULE,
	.read = ppgreader_read,
	.release = ppgreader_release,
};

static int __init ppgreader_module_init(void)
{
	printk(KERN_INFO "Loading ppgreader_module\n");
	alloc_chrdev_region(&ppgreader_dev, 0, 1, "ppgreader_dev");
	printk(KERN_INFO "%s\n", format_dev_t(buffer, ppgreader_dev));

	myclass = class_create(THIS_MODULE, "ppgreader_sys");
	device_create(myclass, NULL, ppgreader_dev, NULL, "ppgreader_dev");

	cdev_init(&ppgreader_cdev, &ppgreader_fops);
	ppgreader_cdev.owner = THIS_MODULE;
	cdev_add(&ppgreader_cdev, ppgreader_dev, 1);
	return 0;
}
static void __exit ppgreader_module_cleanup(void)
{
	printk(KERN_INFO "Cleaning-up ppgreader_dev.\n");
	cdev_del(&ppgreader_cdev);
	unregister_chrdev_region(ppgreader_dev, 1);
}
ssize_t ppgreader_open(struct inode *inodep, struct file *filp)
{
	printk(KERN_INFO "[ppgreader] open\n");
	return 1;
}

module_init(ppgreader_module_init);
module_exit(ppgreader_module_cleanup);
MODULE_AUTHOR("Alessandro Landra");
MODULE_LICENSE("GPL");
