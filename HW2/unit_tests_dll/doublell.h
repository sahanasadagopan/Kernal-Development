#ifndef CM_EXAMPLE_QUADRATIC_H
#define CM_EXAMPLE_QUADRATIC_H

#include <stdint.h>


/* Structure of circular buffer
*@param data
* It is the data that is to be added in the linked list
*@param previous node
* pointing to previous node of the linked list
*@param next node
* Pointing to the next node of the linked list
*/

struct Node{
	uint32_t data;
	struct Node *prev;
	struct Node *next;
};

/* Define the Enum to return the status of sucess or failure*/
enum ll_status{success=1,failure=0};

enum ll_status add_node(struct Node** head,uint32_t data,uint32_t index);

/**
*@brief remove node
* 
*Removes a particular node from a location specified
*
*@param double ptr circular buffer pointer
*
*@param index from which the data is removed
*
*@return status if sucessful or failure
*/

enum ll_status remove_node(struct Node** head,uint32_t index);
/**
*@brief search
* c
*Searhes for a given data 
*
*@param double ptr of linked list
*
*@param data to be located
*
*@return integer value representing the index of the value
*/

uint32_t search(struct Node** head,uint32_t data);

/*
*@brief size
*
*@param double ptr 
*
*@return usigned value of the filled linked list
*
*/
uint32_t size(struct Node** head);

/**
*@brief Delete the whole buffer 
* Makes all the elements in the buffer as NULL and no elements are
* there in the buffer
*
*@param double ptr of the node
*
*@return status if sucess or failure
*/

enum ll_status delete(struct Node** head);

#endif // CM_EXAMPLE_QUADRATIC_H
