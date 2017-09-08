
/***********************************************************************************************
* Copyright (C) 2017 Sahana Sadagopan
*
**Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
*@file circ_buffer.h
*@brief Circular Buffer implementation
*
*This C file provides how to implement circular buffer
*
*@author Sahana Sadagopan
*@date September 2017
*@version 1.0
*
**/

#include <stdio.h>
#include "circbuff.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
circbuff *buffer=NULL;

/**************************************************************************
*   Function - allocate
*   Parameters - double pointer 
*   Returns - status
*   Purpose - Initialises the buffer and the structure in dynamic memory
**************************************************************************/

enum status allocate(circbuff **init_buffer){
	buffer=(circbuff*)malloc(sizeof(circbuff));
	printf("Enter the size of your buffer\n");
	scanf("%d",&(buffer->sizebuff));
	uint32_t* size =NULL;
	size= (uint32_t*)malloc(sizeof(uint32_t)*(buffer->sizebuff));
	if(size==0){
		printf("Not allocated any space\n");
		return failure;
	}
	else{
		buffer->head=size;
		buffer->tail=size;
		buffer->buffer=size;
		*init_buffer=buffer;
		return success;
	}
	
}

/**************************************************************************
*   Function - destroy
*   Parameters - Double pointer buffer
*   Returns - status 
*   Purpose - Destroys the buffer completely and the values inside the buffer is NULL
**************************************************************************/

enum status destroy(circbuff **init_buffer){
	allocate(init_buffer);
	free(init_buffer);
	return success;
}

/**************************************************************************
*   Function - ls_buff_full
*   Parameters - buffer ptr
*   Returns - boolean 
*   Purpose - checks if the buffer is full
**************************************************************************/

bool ls_buff_full(circbuff *buffer)
{
    if(buffer->num_elements==buffer->sizebuff)
    {
            return true;
    }
    else return false;
}

/**************************************************************************
*   Function -ls_buff_empty
*   Parameters - buffer ptr
*   Returns - boolean
*   Purpose - checks if the buffer is empty
**************************************************************************/

bool ls_buff_empty(circbuff *buffer)
{
	if(buffer->num_elements<1)
		return true;
	else
		return false;
}

/**************************************************************************
*   Function - add
*   Parameters - double pointer buffer and elemt to add
*   Returns - status 
*   Purpose - Adds the element to the head of the buffer and it wraps around if the buffer is full
**************************************************************************/

enum status add(circbuff **init_buffer, uint32_t additem){
	buffer= *init_buffer;
	circbuff* allocbuffer=buffer;
	bool buffercheck=ls_buff_full(buffer);
	if(buffercheck){
		printf("buffer full wrapping around\n");
		buffer->num_elements=0;
		buffer->head=buffer->buffer;
	}
		*buffer->head=additem;
		*init_buffer=allocbuffer;
		(*init_buffer)->head=allocbuffer->head;
		(*init_buffer)->num_elements=buffer->num_elements;
		buffer->head++;	
		buffer->num_elements++;
		
		printf("%d\n",buffer->num_elements );
		
		return success;
}

/**************************************************************************
*   Function - delete
*   Parameters - Double pointer buffer
*   Returns - status 
*   Purpose - Delets the element through a pointer at a given point
**************************************************************************/

enum status delete(circbuff **init_buffer){
	printf("deleting item\n");
	bool buffercheck=ls_buff_empty(buffer);
	uint32_t removed=0;
	if(buffercheck) 
		return failure;
	else{
		removed= *buffer->tail;
		printf("removed element:%d\n",removed );
		buffer->tail++;
		buffer->num_elements--;
		return success;
	}
}

/**************************************************************************
*   Function - dump
*   Parameters - Double pointer buffer
*   Returns - status 
*   Purpose - Prints the buffer value 
**************************************************************************/

enum status dump(circbuff **init_buffer)
{
	uint32_t* allocbuffer=buffer->tail;
	if(allocbuffer==NULL){
		printf("Buffer is empty\n");
		return failure;
	}
	else{
		for(int i=0;i<buffer->num_elements;i++){
			printf("The %d buffer element is:%d\n",i,*allocbuffer);
	        allocbuffer++;
		}
		return success;
	}
}

/**************************************************************************
*   Function - size
*   Parameters - No parameters
*   Returns - The number of elements in the circular buffer
*   Purpose - returns the the size of elements in the buffer
**************************************************************************/


uint32_t size(){
	uint32_t size;
	size=(buffer)->num_elements
    return size;
}

int main()
{
	circbuff *initbuffer=NULL;
	allocate(&initbuffer);
	add(&initbuffer,5);
	add(&initbuffer,15);
	add(&initbuffer,34);
	dump(&initbuffer);
	delete(&initbuffer);
	dump(&initbuffer);
	return 0;

}
