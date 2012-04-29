/* first.c - My first Driver code. From L4U.com */
#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>

/*The module now accepts 2 arguements*/
static char *whom = "world";
static int howmany = 10;
static int i = 1;

module_param(howmany, int, S_IRUGO);
module_param(whom, charp, S_IRUGO); 

static int __init first_init(void) /*constructor*/
{
	/*The loop makes use of the module parameters*/
	for(i = 1; i <= howmany; i++)
	{
		printk(KERN_INFO "Hello, %s", whom);
	}
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
