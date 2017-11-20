#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <stdint.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char * argv[]){
	int nbytes;                             // number of bytes send by sendto()
    int sock;                               //this will be our socket
    struct sockaddr_in remote;              //"Internet socket address structure"
    char inputbuff[20],recvbuffer[20];
    unsigned int remote_length;
    
    /******************
      Here we populate a sockaddr_in struct with
      information regarding where we'd like to send our packet 
      i.e the Server.
     ******************/
      printf("%s\n",argv[1] );
    bzero(&remote,sizeof(remote));               //zero the struct
    remote.sin_family = AF_INET;                 //address family
    remote.sin_port = htons(8080);      //sets port to network byte order
    remote.sin_addr.s_addr = inet_addr(argv[1]); //sets remote IP address
    //Causes the system to create a generic socket of type UDP (datagram)
    if ((sock = socket(AF_INET,SOCK_DGRAM,0)) < 0)
    {
        printf("binding\n");
        
    }
    else{
        printf("create socket \n");
    }
	//create_sock(sock);
	printf("Choose ONe among the following mode,frequency,dutyCycle:\n");
	scanf("%s",inputbuff);
    nbytes=sendto(sock,inputbuff,20,0,(struct sockaddr *)&remote, sizeof(remote));
    printf("Enter the Mode of opperation as r,w,all\n");
    scanf("%s",inputbuff);
    nbytes=sendto(sock,inputbuff,20,0,(struct sockaddr *)&remote, sizeof(remote));
    unsigned int addr_length = sizeof(struct sockaddr);
    if(strcmp(inputbuff,"r")==0){
        nbytes=recvfrom(sock,recvbuffer,20,0,(struct sockaddr *)&remote, &addr_length);
        printf("THe value read %s \n",recvbuffer);
    }
    if(strcmp(inputbuff,"w")==0){
        printf("Enter the value to write");
        scanf("%s",recvbuffer);
        nbytes=sendto(sock,recvbuffer,20,0,(struct sockaddr *)&remote, sizeof(remote));
    }
    if(strcmp(inputbuff,"all")==0){
        nbytes=recvfrom(sock,recvbuffer,20,0,(struct sockaddr *)&remote, &addr_length);
        printf("1st mode value %s\n", recvbuffer);
        nbytes=recvfrom(sock,recvbuffer,20,0,(struct sockaddr *)&remote, &addr_length);
        printf("2nd duty value %s\n",recvbuffer );
        nbytes=recvfrom(sock,recvbuffer,20,0,(struct sockaddr *)&remote, &addr_length);
        printf("3rd frequency value %s\n", recvbuffer);
    }

}
