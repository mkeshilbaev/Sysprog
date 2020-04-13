/*
Part 4.
Make a copy of your kernel module code, in a new file. In that file, replace the page-level memory
allocation and deallocation approach with a loop that runs as many times as the value given in the module
paramenter, and in each iteration of the loop (1) uses kmalloc to allocate just enough memory for an
instance of the struct type and then (2) immediately uses kfree to deallocate that memory.
Compile and then load and unload your new module on your Linux kernel, with values 1000 and then
2000 and then 4000 and as the answer to this exercise please say how much time was spent on memory
allocation and deallocation for each of those cases.
*/

#include <linux/module.h>	
#include <linux/kernel.h>	
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/kthread.h>  
#include <linux/moduleparam.h>
#include <linux/time.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADI");

#define TAG "LAB10"

static unsigned int param = 2000;  //default param
module_param(param, int, 0660);

static struct task_struct *thread;

struct my_struct 
{
	unsigned int arr[8];
};

int kmallocLevelAllocation(void *data) 
{	
	struct timespec before;
	getnstimeofday(&before);
	
	int i;
	for(i = 0; i < param; i++) 
	{
		struct my_struct *ptr = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
		if(!ptr) 
			printk(KERN_INFO "ERROR!");
		else 
			kfree(ptr);
	}
	struct timespec after;
	getnstimeofday(&after);
	printk(KERN_INFO "time spent=%ld\n", after.tv_nsec - before.tv_nsec);

	return 0;
}

int init_module(void)
 {
	printk(KERN_INFO "Hello, %u\n", param);

	thread = kthread_run(kmallocLevelAllocation, NULL, "myThread");

	if (thread) 
		printk(KERN_INFO "Thread is created!");
	else
		printk(KERN_INFO "Thread is Not created!");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye :(\n");   
}


