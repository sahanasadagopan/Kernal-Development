#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <mqueue.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define SNDRCV_MQ "/send_recieve_mq"
#define MAX_MSG_SIZE 128
#define ERROR (-1)

struct mq_attr mq_attr;

pthread_t parent;
pthread_t child1;
pthread_t child2;

volatile sig_atomic_t e_flag=0;



void USR1_handler(int signum){
	char ch;
	
	printf("Starting the child thread\n");
	e_flag =1;
	
	
}

void *child1_process(void *threaddp){
	printf("the child \n");
	char *buffer = malloc(sizeof(char)*1000) ;
	FILE *rp = fopen("input.txt","r+");
	fseek(rp,0,SEEK_SET);
	fread(buffer,1,1000,rp);
	printf("Now telling from file\n");
	printf("%s\n",buffer );
	fclose(rp);
}

void *parent_process(void *threaddp){
	struct sigaction thread_sig;
	thread_sig.sa_handler = USR1_handler;
	sigfillset(&thread_sig.sa_mask);
	//thread_sig.sa_flags = SA_SIGINFO;
	printf("The parent thread\n");
	char *buffer=malloc(sizeof(char)*50);
	//printf("%ld\n",e_flag);
	if(sigaction(SIGUSR1,&thread_sig,NULL)<0){
		fprintf(stdout,"wrong sigaction");
	}
	
	FILE *fp = fopen("file","wb+");
	while(e_flag != 1){
		fgets(buffer,sizeof(buffer),stdin);
		fprintf(fp," %s\n",buffer);
		printf("you wrote %s\n",buffer );
		//fputc(buffer,fp);
	}
	fclose(fp);
	/*if(signal(SIGINT,USR1_handler) == SIG_ERR){
		printf("exit failure\n");
	}
	else{
		int ret;
		ret = pthread_create(&child1,(void*)0,child1_process,(void *)0);
	}*/
}

int main(int argc,char *argv[]){
	int ret;
	ret = pthread_create(&parent,(void*)0,parent_process,(void *)0);
	pthread_join(parent,NULL);
}

