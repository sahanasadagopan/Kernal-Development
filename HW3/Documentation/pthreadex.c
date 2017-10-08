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
*@pthreate_create
*@pthread_join
*@getaatr_default
*@pthread_self
*@cond_init
*@cond_wait
*@cond_signal
*@cond_destroy
*@mutex_lock
*@mutex_unlock
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

pthread_t threadfirst;
pthread_t threadsecond;
pthread_t threadthird;
pthread_attr_t BasicThread_attr;

pthread_cond_t cv;
pthread_condattr_t cattr;

pthread_mutex_t count_lock;

int addition=0;
//THe atomic variable for checking the conditons in case of mutex
sig_atomic_t count =0;
//THe First thread that is spwaned
void *BasicThread(void *threadp){
	pthread_t BasicThread;
	BasicThread = pthread_self();
	printf("The thread 1 being executed is %u \n",BasicThread);
	// Mutex is being locked so that the other doesnt get access to the shared memory
	pthread_mutex_lock(&count_lock);
	if(count ==0){
		//Conditional Variables are being set that get when the conditional ]
		//variable is being set
		pthread_cond_signal(&cv);
	}
	count = count +1;
	for (int i = 0; i < 100; ++i)
	{
		addition++;
		printf("increments %d\n", addition);
	}
	// mutex unlock is used to get the lock from the shared resources
	pthread_mutex_unlock(&count_lock);
}

void *SupportThread(void *threadp){
	pthread_t SupportThread;
	SupportThread = pthread_self();
	printf("The thread 2 being executed is %u \n",BasicThread);
	pthread_mutex_lock(&count_lock);
	while(count == 0){
		// Conditional wait it waits till the variable is being set
		pthread_cond_wait(&cv,&count_lock);
	}
	count = count -1;
	int subtraction = addition;
	for(int i =0;i<100;i++){
		subtraction--;
		printf("decrements %d\n", subtraction);
	}
	pthread_cond_destroy(&cv);
	pthread_mutex_unlock(&count_lock);
}

int main(int argc,char *argv[])
{
	int ret;
	size_t stacksize;

	pthread_attr_t IndependentThread_attr;
	/*Getting the default attributes*/
	ret = pthread_getattr_default_np(&BasicThread_attr);
	if(ret != 0){
		fprintf(stderr, "Not set attributes:");
	}
	/*sharing the resources to others*/
	ret = pthread_condattr_setpshared(&cattr,PTHREAD_PROCESS_SHARED);
	if(ret !=0){
		fprintf(stderr, "The resources arent shared or made public\n" );
	}
	/*initialising the conditional variable*/
	ret = pthread_cond_init(&cv,&cattr);
	if(ret != 0){
		fprintf(stderr, "THe conditional varible isnt set correct\n" );
	}
	printf("The stack size is %zd\n",stacksize );
	// creating a child thread
	// CHecking for the error conditions
	ret = pthread_create(&threadfirst,&BasicThread_attr,BasicThread,(void *)0);
	if(ret != 0){
		fprintf(stderr, "Thread not created\n" );
	}
	ret = pthread_create(&threadsecond,(void *)0,SupportThread,(void *)0);
	if(ret != 0){
		fprintf(stderr, "Thread not created \n");
	}
	//pthread_create(&threadthird,(void *)0,IndependentThread,(void *)0);
	//Using pthread_join the get the child threads uspended and back to the parent thread
	ret = pthread_join(threadfirst,NULL);
	if(ret != 0){
		fprintf(stderr, "thread 1 couldnt join\n" );
	}
	ret = pthread_join(threadsecond,NULL);
	if(ret != 0){
		fprintf(stderr, "thread 2 couldnt join\n" );
	}
	//pthread_join(threadthird,NULL);
}
/* Functions left
* mutex_trylock
*get_attr
*set_attr
*mutex_destroy
*pthread_exit*/