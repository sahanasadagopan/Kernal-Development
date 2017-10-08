#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/utsname.h> 
#define NUM 10
#define STACKSIZE 1000000

clock_t curtime,deftime,finatime;

static int childfunc(){
	deftime= clock();
	int i=0;
	int k,j=0;
	//for(i=0;i<9;i++){
		for(j=0;j<NUM;j++){
			k=i+j;
			fprintf(stdout,"The NUmber is %d\n",k );
		}
	//}
	finatime = (long)(curtime-deftime);
	printf("THe time taken for clone is %ld \n",finatime );
}

void main(){
	pid_t pid;
	int i;
	char *stack;
	stack = malloc(STACKSIZE)+ STACKSIZE;
	clock_t execsttime,execstotime,exectime;
	curtime = clock();
	pid = clone(childfunc,stack,CLONE_PARENT,(void *)0);
	//fprintf(stdout,"%ld\n",pid );
}