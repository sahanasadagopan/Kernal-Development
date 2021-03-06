#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <uapi/asm-generic/errno-base.h>
#include <uapi/asm-generic/errno.h>
#include <linux/errno.h>

SYSCALL_DEFINE3(stringcall,int32_t, *buffer, int32_t, bufsize, int32_t, *sortbuf){
	printk(KERN_ALERT "Entering the module \n");
	int32_t *kernel_buffer=NULL;
	int32_t *temp=NULL;
	if(&buffer==NULL){
		printk("invalid param\n");
		return EINVAL;
	}
	if(bufsize<256){
		printk("Please increase the buffer size to 256");
		return ETOOSMALL;
	}
	kernel_buffer= kmalloc((bufsize*(sizeof(int32_t))),GFP_KERNEL);
	temp=kmalloc((bufsize*(sizeof(int32_t))),GFP_KERNEL);
	int32_t res;
	res= copy_from_user(kernel_buffer,buffer,(bufsize*(sizeof(int32_t))));
	if (res !=0){
		printk("The copy from user space was not proper");
		return EFAULT;
	}
	printk(KERN_ALERT "copied to the kernel\n");
	int i;
	int j;
	for(i=0;i<bufsize;i++){
		for(j=0;j<bufsize;j++){
			if(*(kernel_buffer+j)<*(kernel_buffer+j+1)){
				*temp=*(kernel_buffer+j);
				*(kernel_buffer+j)=*(kernel_buffer+j+1);
				*(kernel_buffer+j+1)=*temp;
			}
		}
	}	
	int32_t ses;
	ses = copy_to_user(sortbuf,kernel_buffer,(bufsize*(sizeof(int32_t))));
	if (ses !=0){
		printk("The copy from user space was not proper\n");
		return EFAULT;
	}
	printk(KERN_ALERT "copied back to userspace \n");
	printk(KERN_ALERT "exiting the module\n");
	//free(kernel_buffer);
	return 0;
	
}
