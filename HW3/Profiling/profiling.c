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
#include <sys/wait.h>
#define NUM 300
int main(){
	pid_t pid;
	int ret,status;
	int i;
	/* THe clock variable declared*/
	clock_t curtime,deftime,finatime;
	clock_t execsttime,execstotime,exectime;
	//fprintf(stdout,"%ld seconds 1st epoch\n",(long)curtime);
	uint32_t* buffer = malloc(sizeof(uint32_t)*NUM);
	curtime = clock();
	/*Fork process called*/
	pid=fork();
	if(pid<0)
		printf("fork failed\n");
	if (pid == 0){
		deftime = clock();
		fprintf(stdout,"child process \n");
		finatime = curtime - deftime;
		fprintf(stdout," The time for fork %ld\n",(long)finatime);
		execsttime = clock();
		/*The exec command */ 
		fprintf(stdout, "start %ld\n", execsttime);
		char *args[]={"./example",NULL};
		execv(args[0],args);
		
	}
	execstotime = clock();
	fprintf(stdout, "stop time %ld\n",execstotime );
	exectime = (execstotime-finatime);
	printf("The time for exec %lu\n",exectime);
	if((ret = waitpid(pid,&status,0))==-1)
		printf("Error\n");
	fprintf(stderr, "Parent process \n");
	return 0;
}
