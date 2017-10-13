#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main(){
	int32_t size=256;
	int32_t *buffer=NULL;
	int32_t *sortbuff=NULL;
	buffer=malloc(size*(sizeof(int32_t)));
	sortbuff=malloc(size*(sizeof(int32_t)));
	srand(time(NULL));
	for(int i=0;i<size;i++){
		*buffer=rand()%100;
		buffer++;
	}
	for(int i=0;i<size;i++){
		buffer--;
	}
	for(int i=0;i<size;i++){
		printf("before sorting:%d\n",*(buffer+i) );
	}
	//printf("before sorting:%d\n",buffer);
	syscall(334,buffer,size,sortbuff);
	//printf("%d\n",buffer);
	for(int i=0;i<size;i++){
		printf("The aligned order %i is %d\n",i,*(sortbuff+i) );
	}
}
