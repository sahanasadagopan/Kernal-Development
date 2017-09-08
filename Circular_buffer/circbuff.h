
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
*This header file provides how to add/delete,se
*
*@author Sahana Sadagopan
*@date September 2017
*@version 1.0
*
**/

#ifndef _circbuff_H
#define _circbuff_H
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
/* Enums for the functions declared*/
enum status{success=1,failure=0};

/* Structure of circular buffer
*@param head
* It is the starting point of the buffer
*@param tail 
* pointing to the element that is to be removed
*@param buffer 
* Indicates the start point of the circular buffer
*@param sizebuff
*allocated size of buffer
*@param num_elemenst
*The sizeof the filled buffer
*
*/
typedef struct
{
        uint32_t* head;
        uint32_t* tail;
	    uint32_t* buffer;
        uint32_t sizebuff;
        uint32_t num_elements;
}circbuff;

/**
*@brief checks for buffer full condition
* 
*If the head pointer in the end has reached the end of the buffer
*then the b=function returns a status if the buffer is full or empty
*
*@param ptr circular buffer pointer
*
*@return status in boolean value
*
*/
bool ls_buff_full(circbuff *buffer);
/**
*@brief add item given by the user
*
*@params ptr Buffer pointer
*The buffer poiter and the item to be added is give
*@params Item
*
*@return status
*The status is the result that indicates if the item is added successfully
*/
enum status add_item(circbuff *buffer,uint32_t item);
/**
*@brief the circular buffer is checked if the buffer has elements
*
*@param ptr THe circular buffer pointer
*
*@return It returns a bool value that returns the boolean value
*/
bool ls_buff_empty(circbuff *buffer);
/*
*@brief delete the items in FIFO order
*
*@param ptr The circular buffer pointer
*
*@return status It returns if the deleting the item was succesfull or failure
*/
enum status del_item(circbuff *buffer);

#endif