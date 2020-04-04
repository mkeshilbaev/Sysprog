#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/unistd.h>
#include <linux/sched.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/hrtimer.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("MADI");

#define TAG "LAB10"
#define INTERVAL_BETWEEN_CALLBACKS (100 * 10000000LL) 

int arr[9] = {0, 1, 1, 2, 3, 5, 8, 13, 21}; 
int cnt = 1; 
struct timespec tv; 
static struct hrtimer timer;
static ktime_t kt;

void print_current_time(void) 
{
   getnstimeofday(&tv);
   long long hours = (tv.tv_sec / 3600 + 6) % 24;
   long long minutes = (tv.tv_sec / 60) % 60;
   long long seconds = tv.tv_sec % 60; 
   pr_info("Time : %lld:%lld:%lld", hours, minutes, seconds);
}

static enum hrtimer_restart my_hrtimer_callback( struct hrtimer *timer )
{
    print_current_time();
    printk("Fibonachi num : %d", arr[cnt]);
    s64 now_ns = ktime_to_ns(ktime_get());
    kt = ktime_set(0, arr[cnt]*INTERVAL_BETWEEN_CALLBACKS); 
    hrtimer_forward(timer, timer->_softexpires, kt);
    
    if(cnt <= 8) 
        cnt++;
    return HRTIMER_RESTART;
}
 
static int init_module_hrtimer(void)
{
	printk("START\n");
	kt = ktime_set(0, INTERVAL_BETWEEN_CALLBACKS);
    hrtimer_init(&timer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    hrtimer_start(&timer, kt, HRTIMER_MODE_REL);
    timer.function = my_hrtimer_callback;
    return 0;
}
 
static void cleanup_module_hrtimer(void)
{
	int ret;
	ret = hrtimer_cancel( &timer );
	if (ret)
	printk("Timer is in use\n");
	printk("END\n");
}
 
module_init(init_module_hrtimer);
module_exit(cleanup_module_hrtimer);