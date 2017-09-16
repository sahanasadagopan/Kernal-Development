#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>

SYSCALL_DEFINE3(stringcall,int32_t, *buffer, int32_t, bufsize, int32_t, *sortbuf){
	//buffer= kmalloc((bufsize*(sizeof(int32_t))),GFP_KERNEL);
	int32_t *kernel_buffer=NULL;
	int32_t *temp=NULL;
	kernel_buffer= kmalloc((bufsize*(sizeof(int32_t))),GFP_KERNEL);
	temp=kmalloc((bufsize*(sizeof(int32_t))),GFP_KERNEL);
	int32_t res;
	res= copy_from_user(kernel_buffer,buffer,(bufsize*(sizeof(int32_t))));
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
	return 0;
}
