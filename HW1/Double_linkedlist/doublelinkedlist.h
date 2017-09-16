
/***********************************************************************************************
* Copyright (C) 2017 Sahana Sadagopan
*
**Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Mounika Reddy Edula is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
*@file doublelinkedlist.h
*@brief Double linked list implementation
*
*This header file provides how to implement double linked list
*
*@author Sahana Sadagopan
*@date September 2017
*@version 1.0
*
**/
#ifndef _DOUBLELINKEDLIST_H
#define _DOUBLELINKEDLIST_H


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
enum status{success=1,failure=0};

/**
*@brief Delete the whole buffer 
* Makes all the elements in the buffer as NULL and no elements are
* there in the buffer
*
*@param double ptr of the node
*
*@return status if sucess or failure
*/

enum status delete(struct Node** head);

/**
*@brief Add node
* 
*Node is added with a given data to a particular location
*
*@param double ptr of the linkedlist
*
*@param data to be added
*
*@param index at which data to be added
*
*@return status if sucess or failure
*/

enum status add_node(struct Node** head,uint32_t data,uint32_t index);

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

enum status remove_node(struct Node** head,uint32_t index);

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

#endif /* _DOUBLELINKEDLIST_H__ */
