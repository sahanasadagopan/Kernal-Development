#include <stdio.h>
#include "circbuff.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
circbuff *buffer=NULL;
enum status allocate(circbuff **init_buffer){
	//initialised the struct and allocated memory dynamically
	circbuff* allocbuff;
	init_buffer = (circbuff**)malloc(sizeof(circbuff*));
	allocbuff=(circbuff*)malloc(sizeof(circbuff));
	printf("Enter the size of your buffer\n");
	scanf("%d",&(allocbuff->sizebuff));
	uint32_t* size = (uint32_t*)malloc(sizeof(uint32_t)*(allocbuff->sizebuff));
    buffer=allocbuff;
	if(size==0){
		printf("Not allocated any space\n");
		return failure;
	}
	else{
		//buffer->sizebuff=size;
		//printf("allocating\n");
		buffer->head=size;
		//printf("allocating\n");
		buffer->tail=size;
		buffer->buffer=size;
		*init_buffer=buffer;
		return success;

	}

}

enum status destroy(circbuff **init_buffer){
	allocate(init_buffer);
	free(init_buffer);
	return success;
}

bool buff_full(circbuff *buffer)
{
    if(buffer->num_elements==buffer->sizebuff)
    {
            return true;
    }
    else return false;
}
bool buff_empty(circbuff *buffer)
{
	if(buffer->num_elements<1)
		return true;
	else
		return false;
}

enum status add(circbuff **init_buffer, uint32_t additem){
	buffer=*init_buffer;
	bool buffercheck=buff_full(buffer);
	if(buffercheck){
		buffer->head=buffer->buffer;
		*buffer->head=additem;	
		return success;
	}
	else
		return failure;

}

enum status delete(circbuff **init_buffer){
	buffer=*init_buffer;
	bool buffercheck=buff_empty(buffer);
	uint32_t removed=0;
	if(buffercheck) 
		return failure;
	else{
		//
		removed= *buffer->tail;
		buffer->tail++;
		buffer->num_elements--;
		printf("now pointer at location:%d\n",removed );
		return success;
	}
}

enum status dump(circbuff *buffer)
{
	if(buffer==NULL){
		printf("Buffer is empty\n");
		return failure;
	}
	else{
		for(int i=0;i<buffer->num_elements;i++){
			printf("The %d buffer element is:%d",i,*buffer->head);
	        buffer->head++;
		}
		return success;
	}
}

int main()
{
	circbuff *initbuffer;
    allocate(&initbuffer);
    uint32_t size=0;
    for(int i=0;i<size;i++){
    	add(&initbuffer,i);
	}
	delete(&initbuffer);

	return 0;
	
}
