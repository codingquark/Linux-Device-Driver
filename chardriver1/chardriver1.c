#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

static dev_t first; // Global variable for the first device number

static int __init char_init(void) //Constructor
{
	printk(KERN_INFO "Namaskar. chardriver Registered");
	if (alloc_chrdev_region(&first,0,3,"Dhavan") < 0)
	{
		return -1;
	}

	printk(KERN_INFO "<Major, Minor> : <%d, %d>\n", MAJOR(first), MINOR(first));
	return 0;
}

static void __exit char_exit(void) // destructor
{
	unregister_chrdev_region(first,3);
	printk(KERN_INFO "chardriver Unregistered.");
}

module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHAVAN VAIDYA");
MODULE_DESCRIPTION("First experimental Character Device Driver"); 
