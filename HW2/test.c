#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
void main(){
	uint32_t *buffer;
	uint32_t *sort_buffer = NULL;
	uint32_t *temp=NULL;
	int size;
	scanf("%d/n",&size);
	buffer=malloc( sizeof(uint32_t)*size);
	sort_buffer=malloc(size*(sizeof(uint32_t)));
	temp=malloc(size*(sizeof(uint32_t)));
	srand(time(NULL));
	sort_buffer=buffer;
	for(int i=0;i<size;i++){

		*buffer=rand()%100;
		memcpy(sort_buffer,buffer,sizeof(buffer));
		sort_buffer++;
		buffer++;
	}
	
	for(int i=0;i<(size+1);i++){
		printf("elements are :%d\n", *sort_buffer);
		sort_buffer--;
	}

	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(*(sort_buffer+j)<*(sort_buffer+j+1)){
				*temp=*(sort_buffer+j);
				*(sort_buffer+j)=*(sort_buffer+j+1);
				*(sort_buffer+j+1)=*temp;
			}
		}
	}
	for(int i=0;i<size;i++){
		printf("final buffer %d\n",*sort_buffer );
		sort_buffer++;
	}

}