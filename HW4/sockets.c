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
    char c[2],buffer[20],device[30],read_val[20],write_val[20],recvbuff[20],sendbuff[20];
    int sock;                           //This will be our socket
	struct sockaddr_in sin,remote;     //"Internet socket address structure"
	unsigned int remote_length;         //length of the sockaddr_in structure
	int nbytes;                        //number of bytes we receive in our message

	/******************
	  This code populates the sockaddr_in struct with
	  the information about our socket
	 ******************/
	bzero(&sin,sizeof(sin));                    //zero the struct
	sin.sin_family = AF_INET;                   //address family
	sin.sin_port = htons(8080);        //htons() sets the port # to network byte order
	sin.sin_addr.s_addr = INADDR_ANY;           //supplies the IP address of the local machine


	//Causes the system to create a generic socket of type UDP (datagram)
	if ((sock = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		printf("unable to create socket");
	}
    
    else{
		printf("created socket: descriptor=%d\n", sock);
	}
	/******************
	  Once we've created a socket, we must bind that socket to the 
	  local address and port we've supplied in the sockaddr_in struct
	 ******************/
	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
	{
		printf("unable to bind socket\n");
	}
	else{
		printf("binding\n");
	}
	/**************REcieving the 1st Command**************************************/
	nbytes= recvfrom(sock,recvbuff,20,0,(struct sockaddr *)&remote,&remote_length);
	printf("chosen mode is %s\n",recvbuff);
	//printf("Choose Options mode,dutyCycle,blinkPeriod,all:");
	//scanf("%s",buffer);
	if(strcmp(recvbuff,"all")==0){
	    file=open("/sys/LED_Driver/mode",O_RDWR);
	    file1=open("/sys/LED_Driver/dutyCycle",O_RDWR);
	    file2=open("/sys/LED_Driver/blinkPeriod",O_RDWR);
	}
	else{
	    strcpy(device,"/sys/LED_Driver/");
	    strcat(device,recvbuff);
	    file = open(device, O_RDWR); //open the file for reading and writing.
	}
	/***********************Recieving the second command*********************/
	printf("Enter the Operation:");
	nbytes= recvfrom(sock,recvbuff,20,0,(struct sockaddr *)&remote,&remote_length);
	printf("Choosen operation %s\n",recvbuff);
	if(file == -1) {
		printf("file %s does not exist or has been locked!!\n", device);
		exit(-1);
	}
	/*********************Comparing the operations with user inputs******************************/
	if(strcmp(recvbuff,"r")==0){
	    read(file,read_val,20);
	    strcpy(sendbuff,read_val);
	    //Sending value back to the user
	    nbytes=sendto(sock,sendbuff,20,0,(struct sockaddr *)&remote,sizeof(remote));
	    printf("THe value read is %s\n ", read_val );
	    
	}
	if(strcmp(recvbuff,"w")==0){
		nbytes=recvfrom(sock,recvbuff,20,0,(struct sockaddr *)&remote,&remote_length);
	    printf("value Entered %s",recvbuff);
	    strcpy(write_val,recvbuff);
	    //scanf("%s",write_val);
	    write(file,write_val,20);
	}
	/*******Send all the values of the modes of opperation*****************/
	if(strcmp(recvbuff,"all")==0){
	   read(file,read_val,20);
	   strcpy(sendbuff,read_val);
	   nbytes=sendto(sock,sendbuff,20,0,(struct sockaddr *)&remote,sizeof(remote));
	   printf("THe value read is mode%s ", read_val );
	   read(file1,read_val,20);
	   strcpy(sendbuff,read_val);
	   nbytes=sendto(sock,sendbuff,20,0,(struct sockaddr *)&remote,sizeof(remote));
	   printf("THe value read is duty %s ", read_val );
	   read(file2,read_val,20);
	   strcpy(sendbuff,read_val);
	   nbytes=sendto(sock,sendbuff,20,0,(struct sockaddr *)&remote,sizeof(remote));
	   printf("THe value read is frequency %s ", read_val );
	   close(file1);
	   close(file2);
	    
	}
	close(file);
	return 0;
}
