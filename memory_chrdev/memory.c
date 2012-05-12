#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>

MODULE_LICENSE("Dual BSD/GPL");

int memory_open(struct inode *inode, struct file *filp);
int memory_release(struct inode *inode, struct file *filp);
ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
ssize_t memory_write(struct file *filp, char *buf, size_t count, loff_t *f_pos);
void memory_exit(void);
int memory_init(void);

struct file_operations memory_fops = {
	.owner= THIS_MODULE,
	.read = memory_read,
	.write = memory_write,
	.open = memory_open,
	.release = memory_release
};

module_init(memory_init);
module_exit(memory_exit);

static dev_t memory;
char *memory_buffer;
static struct class *cl;
static struct cdev c_dev;

int __init memory_init(void) {

	if(alloc_chrdev_region(&memory,0,3,"memory") < 0) {
		printk("Cannot obtain major: %d, minor: %d.",MAJOR(memory),MINOR(memory));
		return -1;
	}
	if((cl = class_create(THIS_MODULE, "memory")) == NULL)
	{
		printk(KERN_ALERT "Could not create class.");
		unregister_chrdev_region(memory, 1);
		return -1;
	}

	if(device_create(cl, NULL, memory, NULL, "mymemory") == NULL)
	{	
		printk(KERN_ALERT "Could not create device.");
		class_destroy(cl);
		unregister_chrdev_region(memory, 1);
		return -1;
	}
	cdev_init(&c_dev, &memory_fops);

	if(cdev_add(&c_dev, memory, 1) == -1)
	{
		printk(KERN_INFO "Could not add the c_dev to the memory.");
		device_destroy(cl, memory);
		class_destroy(cl);
		unregister_chrdev_region(memory, 1);
		return -1;
	}

	memory_buffer = kmalloc(1, GFP_KERNEL);

	if(!memory_buffer) {
		return -ENOMEM;
		goto fail;
	}

	memset(memory_buffer, 0, 1);

	printk("<1>Inserting memory module\n");

	fail:
		return -1;
}

void __exit memory_exit(void) {
	cdev_del(&c_dev);
	device_destroy(cl, memory);
	class_destroy(cl);
	unregister_chrdev_region(memory, 1);

	if(memory_buffer)
		kfree(memory_buffer);

	printk(KERN_INFO "Device unregistered.");
}

int memory_open(struct inode *indoe, struct file *filp) {
	return 0;
}

int memory_release(struct inode *inode, struct file *filp) {
	return 0;
}

ssize_t memory_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
	copy_to_user(buf, memory_buffer, 1);

	if(*f_pos == 0) {
		*f_pos+=1;
		return 1;
	} else {
		return 0;
	}

}

ssize_t memory_write(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
	char *tmp;

	tmp = buf + count - 1;
	copy_from_user(memory_buffer,tmp,1);
	return 1;
}


