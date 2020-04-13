/*
Part 2.
In a terminal window on your Linux kernel, run the command
getconf PAGE_SIZE
which will give the size of a kernel memory page, in bytes.
Inside your module, declare a struct type that contains an array of 8 unsigned integers. In your module's
thread function, print a second message to the system log that says how large that struct is (in bytes). You
can use sizeof and the struct type to do this.
As the answer to this exercise, say (1) how large each kernel memory page is, (2) how large the struct
type you declared is, and (3) how many instances of that struct type would fit within a single kernel
memory page.
*/

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/gfp.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/mm_types.h>
#include <linux/types.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADI");

#define TAG "LAB10"
#define PAGE_SIZE 4096

struct mystruct 
{
    unsigned int arr[8];
};

int init_module(void) 
{
    struct mystruct m;
    int temp1 = PAGE_SIZE/sizeof(m);

    printk(KERN_INFO "Hello, part2:");
    printk(KERN_INFO "Page size : %d. \n", PAGE_SIZE);
    printk(KERN_INFO "Struct size : %d. \n", sizeof(m));
    printk(KERN_INFO "Number of instances : %d. \n", temp1);

    return 0;
}

void cleanup_module(void) 
{
    printk(KERN_INFO "Goodbye :(\n");
}