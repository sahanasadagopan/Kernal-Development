#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "quadratic.h"

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
