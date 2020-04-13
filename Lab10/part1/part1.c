/*
Part 1.
Write code for a kernel module that takes a single unsigned integer parameter, which defaults to 2000 if
no value is provided for it. The module's initialization function should create a single kernel thread that is
pinned to one core (which one to use is at your discretion) and that simply outputs a message to the
system log (i.e., using printk) that contains the value of the module parameter (which will be the
number of objects for which memory will be allocated and then deallocated).
Compile your module, and load it on your Linux kernel and check that the message appears in the system
log. Then unload your module and as the answer to this exercise please show the code that implements
your module.
*/

#include <linux/module.h>    
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADI");
#define TAG "LAB10"

static int param = 2000;
module_param(param, int, 0660);

int init_module(void)
{
    printk(KERN_INFO "Part 1:\n");
    printk(KERN_INFO "My module param: .%d\n", param);
}

void cleanup_module(void)
{
    printk("End of Part 1");
}





