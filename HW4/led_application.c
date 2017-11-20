#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <unistd.h>
#include <string.h>

#define BUFFER_LEN 100

int main(){
	
	int i, file,file1,file2;
    char c[2],buffer[20],device[30],read_val[20],write_val[20],recvbuff[20];
    /*******************Taking INputs from the user for the modes**************/
	printf("Choose Options mode,dutyCycle,blinkPeriod,all:");
	scanf("%s",buffer);
	if(strcmp(buffer,"all")==0){
	    file=open("/sys/LED_Driver/mode",O_RDWR);
	    file1=open("/sys/LED_Driver/dutyCycle",O_RDWR);
	    file2=open("/sys/LED_Driver/blinkPeriod",O_RDWR);
	}
	else{
	    strcpy(device,"/sys/LED_Driver/");
	    strcat(device,buffer);
	    file = open(device, O_RDWR); //open the file for reading and writing.
	}
	/*****Choosing read or write or query all opperation***/
	printf("Enter the Operation:");
	scanf("%s", c);
	/***********OPening the file and reading the values**************/
	if(file == -1) {
		printf("file %s does not exist or has been locked!!\n", device);
		exit(-1);
	}
	if(strcmp(c,"r")==0){
	    read(file,read_val,20);
	    printf("THe value read is %s ", read_val );
	    
	}
	/*************If value is write . write into the file with the file descriptor**************/
	if(strcmp(c,"w")==0){
	    printf("Enter the value:");
	    scanf("%s",write_val);
	    write(file,write_val,20);
	}
	if(strcmp(c,"all")==0){
	   read(file,read_val,20);
	   printf("THe value read is mode%s ", read_val );
	   read(file1,read_val,20);
	   printf("THe value read is duty %s ", read_val );
	   read(file2,read_val,20);
	   printf("THe value read is frequency %s ", read_val );
	   close(file1);
	   close(file2);
	    
	}
	close(file);
	return 0;
}
