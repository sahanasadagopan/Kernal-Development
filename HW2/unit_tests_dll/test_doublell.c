/***********************************************************************************************
* Copyright (C) 2017 Sahana Sadagopan
*
**Redistribution,modification or use of this software in source or binary fors is permitted as long 
*as the files maintain this copyright.Sahana Sadagopan is not liable for any misuse of this material
*
*********************************************************************************************************/
/**
*@file doublelinkedlist.h
*@brief Double linked list Test cases
*
*
*@author Sahana Sadagopan
*@date September 2017
*@version 1.0
*
**/
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "doublell.h"

/**************************************************************************
*   Function - add element at the begining 
*   The following test case is used to check the case of addition 
*   the first element to the double linked list
**************************************************************************/

void test_add_begining(void **state){
	struct Node* head= (struct Node*)malloc(sizeof(struct Node));
	uint32_t data=5;
	uint32_t begining=0;
	enum ll_status status = add_node(&head,data,begining);
	assert_int_equal(status,success);
	free(head);
}
/**************************************************************************
*   Function - add element at the center of the linked list
*   The following test case is used to check the case of addition 
*   the element to the double linked list at the center of the 
*   the list. Consider the linked list and the element is added in
*   the center of the list.
************************************************************/
void test_add_center(void **state){
	struct Node* test = (struct Node*)malloc(sizeof(struct Node));
	//uint32_t data=5;
	//uint32_t position=0;
	//add_node(&test,data,position);
	uint32_t position=1;
	uint32_t data=2;
	enum ll_status  status;
	add_node(&test,data,position);
	position=2;
	data=6;
	add_node(&test,data,position);
	position=3;
	data=5;
	status=add_node(&test,data,position);
	assert_int_equal(status,success);
	position=1;
	data=2;
	status=add_node(&test,data,position);
	assert_int_equal(status,success);
	free(test);
}

/**************************************************************************
*   Function - add element at a location where the memory isnt allocated yet
*   The following test case is used to check the case of addition 
*   the fourth  element to the double linked list when the first element 
*   isnt added. THis test would fail as the user cant add fourth element 
*   without adding the 1st element.
**************************************************************************/

void test_add_negative(void **state){
	struct Node *head = malloc(sizeof(struct Node));
	uint32_t data =100;
	uint32_t position = 4;
	enum ll_status status = add_node(&head,data,position);
	assert_int_equal(status,success);
	free(head);
}

/**************************************************************************
*   Function - remove element
*   The following test case is used to check the case of removing
*   the fifth element to the double linked list when there are no
*   elements added to the linked list.
**************************************************************************/

void test_remove_negative(void **state){
	struct Node *test = malloc(sizeof(struct Node));
	uint32_t position = 5;
	enum ll_status status = remove_node(&test,position);
	assert_int_equal(status,success);
	free(test);
}

/**************************************************************************
*   Function - remove element from origin , middle and end 
*   The following test case is used to check the case of removal
*   the first element, 3rd element from middle element and the last element 
*   of the double linked list
**************************************************************************/
void test_remove(void **state){
	struct Node *temp = malloc(sizeof(struct Node));
	uint32_t data =23;
	uint32_t position = 5;
	enum ll_status status;
	add_node(&temp,data,position);
	position=6;
	data=8;
	add_node(&temp,data,position);
	data =10;
	position=7;
	status = add_node(&temp,data,position);
	assert_int_equal(status,success);
	position=0;
	status = remove_node(&temp,position);
	assert_int_equal(status,success);
	position=3;
	status = remove_node(&temp,position);
	assert_int_equal(status,success);
	position=7;
	status = remove_node(&temp,position);
	assert_int_equal(status,success);
	free(temp);

}

/**************************************************************************
*   Function - search elements in the linkedlist
*   The following test case is used to check search function of the linked
*   list.
*   the first element, middle element and the last element 
*   of the double linked list
**************************************************************************/

void test_search(void **state){
	struct Node *head = malloc(sizeof(struct Node));
	uint32_t data = 7;
	uint32_t position =4;
	add_node(&head,data,position);
	data =7;
	uint32_t value = search(&head,data);
	if (value == 4)
		assert_int_equal(value,4);	
	data=5;
	value = search(&head,data);
	if (value == 5)
		assert_int_equal(value,5);	
}


/**************************************************************************
*   Function - size of the double linked list
*   THe following function gives the size of the element when an add and
*   a remove is made
**************************************************************************/

void test_size(void **state){
	struct Node* head=malloc(sizeof(struct Node));
	uint32_t size_node = size(&head);
	if (size_node == 4){
		assert_int_equal(size_node,4);
	}
	free(head);

}
/**************************************************************************
*   Function - destroying the linked list
*   THe following function completely destroys the whole linked list.
**************************************************************************/


void test_delete(void **state){
	struct Node* head=(struct Node*)malloc(sizeof(struct Node));
	enum ll_status status = delete(&head);
	assert_int_equal(status,success);

}

int main(int argc,char **argv){
	const struct CMUnitTest tests[] ={
		cmocka_unit_test(test_add_negative),
		cmocka_unit_test(test_add_begining),
		cmocka_unit_test(test_add_center),
		cmocka_unit_test(test_remove),
		cmocka_unit_test(test_search),
		cmocka_unit_test(test_size),
		cmocka_unit_test(test_remove_negative),
		cmocka_unit_test(test_delete)		
	};
	return cmocka_run_group_tests(tests,NULL,NULL);
}
