/**
 * CS 2110 - Spring 2015 - Homework #10
 * Edited by: Brandon Whitehead, Andrew Wilder
 *
 * list.h
 */

#ifndef LIST_H
#define LIST_H


/***************************************
 ** Datatype definitions DO NOT TOUCH **
 ***************************************/

/* Forward declaration 
Don't know what a forward declaration is? 
Consult the fountain of knowledge: http://en.wikipedia.org/wiki/Forward_declaration */
struct lnode;

/* Given to you for free, However you better know how to do this come time for the final exam */
/* The linked list struct.  Has a head & tail pointer. */
typedef struct llist
{
  struct lnode* head; /* Head pointer either points to a node with data or NULL */
  struct lnode* tail; /* Tail pointer either points to a node with data or NULL */
  unsigned int size; /* Size of the linked list */
} list;

/* Given to you for free, However you better know how to do this come time for the final exam */
/* A function pointer type that points to a function that takes in a void* and returns nothing, call it list_op */
typedef void (*list_op)(void*);
/* A function pointer type that points to a function that takes in a const void* and returns an int, call it list_pred */
typedef int (*list_pred)(const void*);
/* A function pointer type that points to a function that takes in a void* and returns a void*, call it list_cpy */
typedef void* (*list_cpy)(const void*);

/**************************************************
** Prototypes for linked list library functions. **
**                                               **
** For more details on their functionality,      **
** check list.c.                                 **
***************************************************/

/* Creating */
list* create_list(void);
list* copy_list(list* llist, list_cpy copy_func);

/* Adding */
void push_front(list* llist, void* data);
void push_back(list* llist, void* data);

/* Removing */
int remove_front(list* llist, list_op free_func);
int remove_back(list* llist, list_op free_func);
int remove_if(list* llist, list_pred pred_func, list_op free_func);

/* Querying List */
void* front(list* llist);
void* back(list* llist);
int is_empty(list* llist);
int size(list* llist);

/* Freeing */
void empty_list(list* llist, list_op free_func);

/* Traversal */
void traverse(list* llist, list_op do_func);

#endif

