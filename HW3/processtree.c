#include <stdlib.h>
#include <stdio.h>
#include "list.h"


typedef struct episode {
  int epid;
  struct list_head list;
} episode_t;


typedef struct program {
  int pid;
  struct list_head list;
  struct list_head episode_list;
} program_t;


int main(void)
{
  LIST_HEAD(program_list);

  program_t *ptr;
  int i;
  for (i = 0; i < 5; i++ ) {
    ptr = malloc(sizeof(*ptr));
    ptr->pid = i;
    INIT_LIST_HEAD(&ptr->list);
    INIT_LIST_HEAD(&ptr->episode_list);
    list_add_tail(&ptr->list, &program_list);

    int j;
    episode_t *eptr;
    for (j = 10; j < 15; j++) {
      eptr = malloc(sizeof(*eptr));
      eptr->epid = j;
      INIT_LIST_HEAD(&eptr->list);
      list_add_tail(&eptr->list, &ptr->episode_list);
      
    }
  }

  //traverse list
  list_for_each_entry(ptr,&program_list, list){
    printf("pid: %d\n", ptr->pid);

    episode_t *eptr;
    list_for_each_entry(eptr, &ptr->episode_list, list) {
      printf("epid: %d\n", eptr->epid);
    }
  }


  //delete node
  program_t *next;
  list_for_each_entry_safe(ptr, next, &program_list, list) {
    printf("Removing – pid: %d\n", ptr->pid);

    episode_t *enext, *eptr;
    list_for_each_entry_safe(eptr, enext, &ptr->episode_list, list) {
      printf("Removing – epid: %d\n", eptr->epid);
      list_del(&eptr->list);
      free(eptr);
    }
    
    list_del(&ptr->list);
    free(ptr);
  }
  
  printf("list\n");

  //traverse list
  list_for_each_entry(ptr,&program_list, list){
    printf("pid: %d\n", ptr->pid);

    episode_t *eptr;
    list_for_each_entry(eptr, &ptr->episode_list, list) {
      printf("epid: %d\n", eptr->epid);
    }
  }

}