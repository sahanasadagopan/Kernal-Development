/***********************************************************************************************
* Copyright (C) 2017 Sahana Sadagopan
*
**Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Sahana Sadagopan is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
*@file Pthread Documentation
*@brief Pthtread api implementation
*
*This header file provides how to Use the following api
*
*@getattr
*@setattr
*@mutex_trylock
*@pthread_exit
*
*@author Sahana Sadagopan
*@date September 2017
*@version 1.0
*
**/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>

pthread_t status_thread;
pthread_t computation_thread;

pthread_attr_t attr_set;
struct sched_param set_sched_param;

pthread_mutex_t compmutex;

struct file{
	FILE *fp;
	char *filename;
}filedetail;

void *get_attr(void *threaddp){
	int ret;
	size_t guard_size,stack_size;
	void *stackaddr;
	int i;
	printf("The thread parameters\n");
	ret = pthread_getattr_np(pthread_self(),&attr_set);
	if(ret != 0){
		perror("insufficient memory \n ");
	}
	ret = pthread_attr_getguardsize(&attr_set,&guard_size);
	if (ret ==0){
		perror("appropriate guard size\n");
	}
	printf("Guard size: %zu \n",guard_size);
	ret = pthread_attr_getstack(&attr_set,&stackaddr,&stack_size);
	if(ret != 0){
		perror("Error in stacksize allocation\n");
	}
	printf("Stack address %zu\n",stackaddr);
	ret = pthread_attr_getschedparam(&attr_set,&set_sched_param);
	if(ret !=0){
		perror("Thread params not set\n");
	}
	printf("The sched params %d\n",set_sched_param.sched_priority );
	ret = pthread_attr_getschedpolicy(&attr_set,&i);
	if(ret !=0 ){
		perror("Policy not set");
	}
	printf("The policy is %d \n",set_sched_param.sched_priority);
	pthread_exit(NULL);
}

void *compute(void *threaddp){
	printf("Computation started\n");
	if(pthread_mutex_trylock(&compmutex)==0){
		for(int i=0;i<100;i++){
			fprintf(stdout, "%d\n",i );
		}
	pthread_mutex_unlock(&compmutex);	
	}
	pthread_exit(NULL);
}

int main(int argc,char *argv[])
{
	int ret;
	int i;
	size_t guard_size,stack_size;
	void *stackaddr;
	size_t psize = getpagesize();
	ret = pthread_attr_setguardsize(&attr_set,psize);
	if (ret != 0){
		printf("Error\n");
	}
	ret = pthread_attr_setschedpolicy(&attr_set,SCHED_FIFO);
	if (ret != 0){
		printf("Error\n");
	}
	ret = pthread_attr_setschedparam(&attr_set,&set_sched_param);
	if (ret != 0){
		printf("Error\n");
	}
	set_sched_param.sched_priority = 1;
	pthread_mutex_init(&compmutex,NULL);
	ret=pthread_create(&status_thread,&attr_set,get_attr,(void*)0);
	if(ret !=0){
		fprintf(stderr, "thread not created" );
	}
	pthread_create(&computation_thread,&attr_set,compute,(void *)0);
	pthread_attr_destroy(&attr_set);
	pthread_join(status_thread,NULL);
	pthread_join(computation_thread,NULL);
	pthread_exit(NULL);
}
