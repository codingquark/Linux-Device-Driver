/* first.c - My first Driver code. From L4U.com */
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

static int __init first_init(void) /*constructor*/
{
	printk(KERN_INFO "Hello, world.");
	return 0;
}

static void __exit first_exit(void) /*destructor*/
{
	printk(KERN_INFO "Goodbye, cruel world.");
}

module_init(first_init); /* Fisrt macro being called for constructor*/
module_exit(first_exit); /* macro for destructor */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dhavan Vaidya");
MODULE_DESCRIPTION("My first Driver");
