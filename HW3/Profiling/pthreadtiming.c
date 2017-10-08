#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t Childthread;
clock_t start_time,endtime,timediff;

void *func1(void *threaddp){
	//timer end
	endtime=clock();
	timediff=(long) (endtime-start_time);
	printf("The time of the childthread is %ld\n",timediff );
}

void main(){
	int ret;
	//timer started
	start_time=clock();
	/*pthread create*/
	ret = pthread_create(&Childthread,(void *)0,func1,(void *)0);
	ret = pthread_join(Childthread,NULL);
}