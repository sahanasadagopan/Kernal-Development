#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

volatile sig_atomic_t status =0;
volatile sig_atomic_t sigprint =0;

pthread_t child1;
/*structure for counts*/
struct report_stat{
  int linecount;
  int wordcount;
  int charcount;
  char *filename;
}stats;

static void int_handler(){
  char ch;
  printf("Enter y to close the program ");
  scanf("%c",&ch);
  if(ch == 'y'){
    fprintf(stdout, "close program \n");
  }
}
/*1st handler*/
static void hdl (int sig, siginfo_t *siginfo, void *context)
{
  printf ("Sending PID Signal 1 is got: %ld, UID: %ld\n",(long)siginfo->si_pid, (long)siginfo->si_uid);
  status=1;
}
/*second handle*/
static void hdl2 (int sig,siginfo_t *siginfo, void *context){
  printf("This is signal 2 id got\n");
  sigprint =1;
}
/* THe child that prints the computation*/
void *child2_process(void *threaddp){
  fprintf(stdout, "pid %d\n",getpid() );
  if(sigprint==1){
    fprintf(stdout, "count line %d count words %d charcount %d \n",
                stats.linecount,stats.wordcount,stats.charcount);
  }

}

/*First child thread that does the computation*/  
void *child1_process(void *threaddp){
  char *buffer= malloc(sizeof(char)*50);
  char *filename = malloc(sizeof(char)*20);
  char c;
  filename = stats.filename;
  stats.linecount=0,stats.wordcount=0,stats.charcount=0;
  pid_t pid = getpid();
  fprintf(stdout, "pid %d\n",pid );
  FILE *rp = fopen(filename,"rb");
  while((c=fgetc(rp))!= EOF){  
    fprintf(stdout,"%c",c );
    if(c == '\n'){
      stats.linecount++;
    }
    if(c == ' ' || c == '\n'){
      stats.wordcount++;
    }
    if(c != ' ' && c != '\n'){
      stats.charcount++;
    }
  }
  fprintf(stdout, "count line %d count words %d charcount %d \n",
              stats.linecount,stats.wordcount,stats.charcount);
  fclose(rp);
}
/* THe main parent thread*/
int main (int argc, char *argv[])
{
  int ret ;
  char *msg=malloc(sizeof(char)*500);
  /*sigaction variables initialised*/
  struct sigaction act1;
  act1.sa_sigaction = &hdl;
  act1.sa_flags = SA_SIGINFO;
  struct sigaction act2;
  act2.sa_sigaction = &hdl2;
  act2.sa_flags = SA_SIGINFO;
  char *filename = malloc(sizeof(char)*20);

  fprintf(stdout, "pid %d\n",getpid() );
  //sigaction called
  if (sigaction(SIGUSR1, &act1, NULL) < 0) {
    perror ("sigaction");
    return (-1);
  }

  if (sigaction(SIGUSR2, &act2, NULL) < 0) {
    perror ("sigaction");
    fprintf(stdout, "incorrect signal\n");
    return (-1);
  }
  signal(SIGINT,int_handler);
  printf("Enter the filename ");
  scanf("%s\n",filename);
  //File opened
  stats.filename = filename;
  FILE *fp = fopen(filename,"wb+");
  while (status != 1 || sigprint != 1){
    fgets(msg,500,stdin);
    fputs(msg,fp);
  }
  ret = fclose(fp);
  if(ret == EOF){
      perror("The error was");
  }
  //Two childthread created
  if((pthread_create(&child1,(void*)0,child1_process,(void *)0))==0)
    printf("success");
  if((pthread_create(&child2,(void*)0,child2_process,(void *)0))==0)
  {
    printf("success 2");
  }
  pthread_join(child1,NULL);
  pthread_join(child2,NULL);
  return 0;
}