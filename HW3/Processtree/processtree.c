#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Sahana");
MODULE_DESCRIPTION("Kernel processinfo");

struct task_struct *task;
struct list_head *list;


static int __init processinfo_init(void){
	pid_t pid;
	pid = getpid();
	printk("The current threads pid is %d\n",pid);
	int findchildren;
	struct task_struct *my_parent = current->parent;
	printk(KERN_INFO "my parent%d\n",my_parent->pid );
	return 0;
}

static void __exit processinfo_cleanup(void){
	printk(KERN_INFO"Cleaning up module \n");
}

module_init(processinfo_init);
module_exit(processinfo_cleanup);