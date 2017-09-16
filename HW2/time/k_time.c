#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Sahana");
MODULE_DESCRIPTION("Kernel Timer");
static struct timer_list kern_timer;

/*void timemod_func(unsigned long data){
	int err_check;
	err_check=mod_timer(&kern_timer,jiffies+msecs_to_jiffies(500));
	if(err_check){
		printk("Error in timer");
	}
}*/

void kern_timer_callback(unsigned long data){
	static int count;
	count++;
	printk("The timer is printed id %d",count);
	int err_check;
	err_check=mod_timer(&kern_timer,jiffies+msecs_to_jiffies(500));
	if(err_check){
		printk("Error in timer");
	}
	//kern_timer.function = timemod_func;
	//kern_timer.expires = jiffies + msecs_to_jiffies(500);
	//kern_timer.data = (unsigned long) data ;
	//add_timer(&kern_timer);

}

static int timemod_init(void)
{
	setup_timer( &kern_timer ,kern_timer_callback,0);
	printk("Starting a timer in 500ms (%ld",jiffies);
	int err_check;
	err_check=mod_timer(&kern_timer,jiffies+msecs_to_jiffies(500));
	if(err_check){
		printk("Error in timer");
	}
	return 0;	

}

static void timemod_exit(void)
{
	int ret;
	ret = del_timer(&kern_timer);
	if(ret){
		printk("timer deleted");
	}
	return 0;
} 

module_init(timemod_init);
module_exit(timemod_exit);
