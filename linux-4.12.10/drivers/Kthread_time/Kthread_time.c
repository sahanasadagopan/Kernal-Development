#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Sahana");
MODULE_DESCRIPTION("Kernel Timer");
//static struct timer_list kern_timer;
static struct task_struct *thread;
u64 j0;

static int time_calc(void *arg){
	
	printk(KERN_INFO"kernel timer created");
	

}

static int ktime_init(void)
{
	u64 j1,j2;
	//char mythread[20] = "Mythread";
	printk(KERN_INFO "INIT_module");
	j0=get_jiffies_64();
	printk(KERN_INFO"start time %lu\n",j0 );
	thread = kthread_create(time_calc,NULL,"mythread");
	j1 = get_jiffies_64();
	j2 = j1 -j0;
	printk(KERN_INFO"the time in jiffies is %ld",j2);
	if((thread)){
		printk(KERN_INFO"created thread");
	}
	return 0;

}

static void ktime_exit(void){
	int ret;
	ret = kthread_stop(thread);
	if(!ret)
		printk(KERN_INFO"THread stopped");
}


module_init(ktime_init);
module_exit(ktime_exit);
