/***********************************************************************************************
* Copyright (C) 2017 Sahana Sadagopan
*
**Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Sahana Sadagopan is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
*@file doublelinkedlist.h
*@brief Double linked list implementation
*
*This header file provides how to add/delete,se
*
*@author Sahana Sadagopan
*@date September 2017
*@version 1.0
*
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "doublelinkedlist.h"

/*global variable*/
static uint32_t count=0;

/**************************************************************************
*   Function - delete
*   Parameters - double pointer poiting to the node
*   Returns - status
*   Purpose - Deletes all the elements in the linked list
**************************************************************************/

enum status delete(struct Node** head){
	struct Node* temp = malloc(sizeof(struct Node));
	temp =*head;
	if(temp->next != NULL){
	    while (*head=temp)
		{
			*head=temp->next;
			temp=temp->next;
		}
	}
    return success;
     

}

/**************************************************************************
*   Function - remove_node
*   Parameters - double pointer to nodew,index 
*   Returns - status
*   Purpose - remove the node at the particular index
**************************************************************************/

enum status remove_node(struct Node** head,uint32_t index){

	struct Node* temp=*head;
	struct Node* current=temp;
	if(temp==NULL){
        printf("empty list\n");
        return failure;
    }

    else{
	    if (index==0)
	    { temp=temp->next;
	    	*head=temp;
	    }
	    else {
	        for(int i=1; i<index; ++i)
	            current=current->next;
            struct Node *temp1=malloc(sizeof(struct Node));
            temp1=current->next;
            current->next=temp1->next;
        	*head=temp;
	    }
    }
	return success;
}

/**************************************************************************
*   Function - add_node
*   Parameters - double pointer Node and data and index
*   Returns - status
*   Purpose -adds a new node at a given index to add particular data
**************************************************************************/

enum status add_node(struct Node** head,uint32_t data,uint32_t index)
{
	struct Node* newnode = malloc(sizeof(struct Node));
	struct Node* temp = *head;
    struct Node* permanent =temp;
    if(index==0){
	    if(index==count){
			newnode->data=data;
			newnode->next=temp;

			temp=newnode;
			
			*head=temp;
			
			count++;
		}
		else{
			 temp=temp->next;
			 count++;
			 add_node(&temp,data,index);
			}
	}
	else{
		struct Node* current =temp;
		for(int i=1;i<index;i++){
			temp = temp->next;
		}
		newnode->data =data;
		newnode->next=temp->next;
		temp->next=newnode;
		*head=current;
	}
    return success;

    
}
/**************************************************************************
*   Function - search
*   Parameters - double pointer to NOde and data to find
*   Returns - status
*   Purpose - Searches throughout the linked list
*             to find the index of the number
**************************************************************************/

uint32_t search(struct Node** head,uint32_t data){
	static uint32_t position =0;
	struct Node* temp=malloc(sizeof(struct Node));
	if(head==NULL){
		printf("Linked list empty \n");
		
	}
	temp=*head;
	while(temp!=NULL){
		if(data==temp->data){
			break;
			
		}
		else
		{
			temp=temp->next;
			position++;
		}
	}
	return position;



}
/**************************************************************************
*   Function - size
*   Parameters - DOuble pointer pointing to the Node
*   Returns - NO of nodes present in the linked list
*   Purpose - returns the the size of the linked list that is filled
**************************************************************************/
uint32_t size(struct Node** head){
	struct Node* temp=malloc(sizeof(struct Node));
	temp=*head;
	uint32_t size;
	while(temp!=NULL){
		size++;
		temp=temp->next;
	}
	free(temp);
	return size;
}



void main(){

	struct Node *head= malloc(sizeof(struct Node));
    uint32_t placeholder=0;
    add_node(&head,1,placeholder);
    placeholder=1;
    add_node(&head,3,placeholder);
    add_node(&head,2,2);
    remove_node(&head,1);
    uint32_t value = search(&head,2);
    printf("search index %d\n",value );
    int a =delete(&head);
    printf("%d\n",a );
    free(head);
}
