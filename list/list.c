/**
 * CS 2110 - Spring 2015 - Homework #10
 * Edited by: Brandon Whitehead, Andrew Wilder
 *
 * list.c: Complete the functions!
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    node* newnode = (node*)malloc(sizeof(node));
    if (newnode == 0) {
        printf("Out of memory.\n");
        return NULL;
    }
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;
    return newnode;
}

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
    list* newlist = (list*)malloc(sizeof(list));
    if (newlist == 0) {
        printf("Out of memory.\n");
        return NULL;
    }
    newlist->size = 0;
    newlist->head = NULL;
    newlist->tail = NULL;
    return newlist;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
    if (is_empty(llist) != 1) {
        llist->head->prev = create_node(data);
        llist->head->prev->next = llist->head;
        llist->head = llist->head->prev;
    } else {
        llist->head = create_node(data);
        llist->tail = llist->head;
    }
    llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
    if (is_empty(llist) != 1) {
        llist->tail->next = create_node(data);
        llist->tail->next->prev = llist->tail;
        llist->tail = llist->tail->next;
    } else {
        llist->head = create_node(data);
        llist->tail = llist->head;
    }
    llist->size++;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
    if (is_empty(llist) != 1) {
        return llist->head->data;
    }
    return NULL;
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
    if (is_empty(llist) != 1) {
        return llist->tail->data;
    }
    return NULL;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
    if (is_empty(llist) != 1) {
        free_func(llist->head->data);
        llist->head = llist->head->next;
        if (llist->head == NULL) {
            llist->tail = NULL;
        } else {
            free(llist->head->prev);
            llist->head->prev = NULL;
        }
        llist->size--;
        return 0;
    }
    return -1;
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    if (is_empty(llist) != 1) {
        free_func(llist->tail->data);
        llist->tail = llist->tail->prev;
        if (llist->tail == NULL) {
            llist->head = NULL;
        } else {
            free(llist->tail->next);
            llist->tail->next = NULL;
        }
        llist->size--;
        return 0;
    }
    return -1;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data by using
  * the copy function. Its implementation for any test structure must copy
  * EVERYTHING!
  *
  * @param llist A pointer to the linked list to make a copy of
  * @param copy_func A function pointer to a function that makes a copy of the
  *        data that's being used in this linked list, allocating space for
  *        every part of that data on the heap. This is some function you must
  *        write yourself for testing, tailored specifically to whatever context
  *        you're using the linked list for in your test.
  * @return The linked list created by copying the old one
  */
list* copy_list(list* llist, list_cpy copy_func)
{
    list* newlist = create_list();
    if (is_empty(llist) != 1) {
        newlist->size = llist->size;
        newlist->head = create_node(copy_func(llist->head->data));
        node* curr = llist->head->next;
        node* ncurr = newlist->head;
        while (curr != NULL) {
            ncurr->next = create_node(copy_func(curr->data));
            ncurr->next->prev = ncurr;
            ncurr = ncurr->next;
            curr = curr->next;
        }
        newlist->tail = ncurr;
    }
    return newlist;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    return llist->size;
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
    /// @todo Implement changing the return value!
    /// @note remember to also free all nodes you remove.
    /// @note be sure to call pred_func on the NODES DATA to check if the node needs to be removed.
    /// @note free_func is a function that is responsible for freeing the node's data only.
    int counter = 0;
    if (is_empty(llist) != 1) {
      node* curr = llist->head;
      while (curr != NULL) {
          printf("ok\n");
          if (pred_func(curr->data) == 1) {
              if (curr != llist->head && curr!= llist->tail) {
                  free_func(curr->data);
                  curr->prev->next = curr->next;
                  curr->next->prev = curr->prev;
                  free(curr);
                  curr = curr->next;
                  llist->size--;
              } else if (curr == llist->head) {
                  remove_front(llist, free_func);
                  curr = llist->head;
              } else if (curr == llist->tail) {
                  remove_back(llist, free_func);
                  curr = llist->tail;
              }
              counter++;
          } else {
              curr = curr->next;
          }
        }
    }
    return counter;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    ///@note an empty list by the way we want you to implement it has a size of zero and head points to NULL.
    if ((llist->size == 0) && (llist->head == NULL)) {
        return 1;
    }
    return 0;
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  */
void empty_list(list* llist, list_op free_func)
{
    /// @todo Implement
    /// @note Free all of the nodes not the linked list itself.
    /// @note do not free llist.
    if (is_empty(llist) != 1) {
        node* curr = llist->head;
        while (curr != NULL) {
            free_func(curr->data);
            free(curr);
            curr = curr->next;
        }
        llist->size = 0;
        llist->head = NULL;
        llist->tail = NULL;
    }
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
    if (is_empty(llist) != 1) {
        node* curr = llist->head;
        while (curr != NULL) {
            do_func(curr->data);
            curr = curr->next;
        }
    }    
}
