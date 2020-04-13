/*
Part 5.
Copy that version of your kernel module into a new file, and change the memory allocation and
deallocation scheme to use slab allocation. Specifically, your new module's init function should use
kmem_cache_create to create a new cache for the module's struct type, and store a pointer to it in a
global variable, and your new module's exit function should use kmem_cache_destroy to destroy
the cache. Then inside the loop within the thread function of your new module, replace the calls to
kmalloc and kfree with appropriate calls to kmem_cache_alloc and kmem_cache_free
respectively, instead.
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

static unsigned int param = 2000;
module_param(param, int, 0660);

static struct task_struct *thread;
static struct kmem_cache *my_cache;

struct my_struct 
{
	unsigned int arr[8];
};

int slabLevelAllocation(void *data) 
{	
	struct timespec before;
	getnstimeofday(&before);
	
	int i;
	for(i = 0; i < param; i++) 
	{
		struct my_struct *ptr = kmem_cache_alloc(my_cache, GFP_KERNEL);
		if (!ptr) 
			printk(KERN_INFO "error!");
		  else 
			kmem_cache_free(my_cache, ptr);
	}
	struct timespec after;
	getnstimeofday(&after);
	printk(KERN_INFO "time spent=%ld\n", after.tv_nsec - before.tv_nsec);

	return 0;
}

int init_module(void) 
{
	printk(KERN_INFO "Hello, %u\n", param);
	my_cache = kmem_cache_create("my cache", sizeof(struct my_struct), ARCH_MIN_TASKALIGN, 0, NULL);

	if (my_cache)
		printk(KERN_INFO "Cache is created!");
	thread = kthread_run(slabLevelAllocation, NULL, "myThread");

	if (thread) 
		printk(KERN_INFO "Thread is created!");
	else
		printk(KERN_INFO "Thread is Not created!");
	return 0;
}

void cleanup_module(void)
{
	kmem_cache_destroy(my_cache);
	printk(KERN_INFO "Goodbye :(\n");   
}

