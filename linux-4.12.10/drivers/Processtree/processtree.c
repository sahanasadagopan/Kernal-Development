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

/*void callback(struct task_struct *old_parent,struct task_struct *updated_current){
	updated_current=old_parent->parent;
	printk(KERN_INFO"IN here %d \n",updated_current->pid);
}*/

static int __init processinfo_init(void){
	int findchildren;
	//struct task_struct *my_parent = current->parent;
	//printk(KERN_INFO "my parent %d\n",my_parent->pid );
	//printk(KERN_INFO"my pid %d \n",current->pid);
	printk(KERN_INFO"STARTED MODULE");
	rcu_read_lock();
	for(task = current;task !=&init_task;task=task->parent){
		findchildren =0;
		list_for_each(list,& task->children){
			findchildren++;
			
		}
		printk(KERN_INFO "The number of children to the process %d",findchildren);
		printk(KERN_INFO"updated current %d \n",task->pid);
		printk(KERN_INFO"The status of the task %d \n",task->state);
		printk(KERN_INFO"The name of process %s \n ",task->comm);
	}
	rcu_read_unlock();
	printk(KERN_INFO"loop ended");
	
	//for_each_process(task){
	//printk(KERN_INFO"1st task %s %d", task->comm,task->pid);
	//}
	
	return 0;
}

static void __exit processinfo_cleanup(void){
	printk(KERN_INFO"Cleaning up module \n");
}

module_init(processinfo_init);
module_exit(processinfo_cleanup);
