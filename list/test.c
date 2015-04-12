#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores
 * Person data (name, age)
 */
typedef struct person_t
{
    char* name;
    int age;
} Person;

/* Example functions given to you. If you want to truly grasp these concepts, try
 * writing your own structs and functions as well!
 */

// Create a new Person
Person* create_person(const char* name, int age)
{
    Person* p = (Person*) malloc(sizeof(Person));
    p->name = strdup(name); // Uses malloc!
    p->age = age;
    return p;
}

// Make a deep copy of a Person
void* copy_person(const void* data)
{
    Person *p = (Person*) data;
    return create_person(p->name, p->age);
}

// Print a Person
void print_person(void* data)
{
    Person *p = (Person*) data;
    printf("%s, %d\n", p->name, p->age);
}

// Free a Person
void free_person(void* data)
{
    // This is safe because we should only be passing in Person struct pointers
    Person *p = (Person*) data;
    // free any malloc'd pointers contained in the Person struct (just name)
    free(p->name);
    // Now free the struct itself; this takes care of non-malloc'd data, like age.
    free(p);
}

int check_person(const void* data) {
    Person *p = (Person*) data;
    if (p->age > 21) {
        return 1;
    }
    return 0;
}

// Return 1 if the person's name is 8+ characters long
int long_name(const void *data)
{
	Person *p = (Person*) data;
	return strlen(p->name) > 4;
}

/* This main function does a little testing
   Like all good CS Majors you should test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void)
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();

  /* What does an empty list contain?  Lets use our handy traversal function */
  printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  traverse(llist, print_person);
  printf("Size: %d\n", llist->size);
	printf("\n");

 	/* Lets add a person and then print */
 	push_front(llist, create_person("Andrew", 24));
 	printf("TEST CASE 2\nA List with one person should print that person:\n");
 	traverse(llist, print_person);
  printf("Size: %d\n", llist->size);
 	printf("\n");

  /* Lets remove that person and then print */
  remove_front(llist, free_person);
  printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
  traverse(llist, print_person);
  printf("Size: %d\n", llist->size);
  printf("\n");

  /* Lets add four people and then print */
  push_front(llist, create_person("Nick", 22));
  push_back(llist, create_person("Randal", 21));
  push_back(llist, create_person("Alex", 30));
  push_back(llist, create_person("James", 15));
  printf("TEST CASE 4\nA List with two people should print those two people:\n");
  traverse(llist, print_person);
  printf("Size: %d\n", llist->size);
  printf("\n");

  /* Lets test remove_if first time */
  remove_if(llist, check_person, free_person);
  printf("TEST CASE 5\nA List with two people should print those two people:\n");
  traverse(llist, print_person);
  printf("Size: %d\n", llist->size);
  printf("\n");

  /* Lets copy this list */
  list* llist2 = copy_list(llist, copy_person);
  printf("TEST CASE 6\nA copied list should print out the same two people:\n");
  traverse(llist2, print_person);
  printf("Size: %d\n", llist->size);
  printf("\n");

  /* Lets kill the list */
  empty_list(llist, free_person);
  printf("TEST CASE 7\nAfter freeing all nodes the list should be empty:\n");
  traverse(llist, print_person);
  printf("Size: %d\n", llist->size);
  printf("\n");

  /* Let's make a list of people, and remove certain ones! */
  /* Should remove anyone whose name is 8+ characters long */
  push_front(llist, create_person("Josephine", 27));
  push_front(llist, create_person("Dave", 34));
  push_front(llist, create_person("Benjamin", 23));
  push_front(llist, create_person("Lisa", 41));
  push_front(llist, create_person("Maximilian", 24));
  remove_if(llist, long_name, free_person);
  printf("TEST CASE 8\nShould only print 2 people with short names:\n");
  traverse(llist, print_person);
  printf("Size: %d\n", llist->size);
  printf("\n");

  /* YOU ARE REQUIRED TO MAKE MORE TEST CASES THAN THE ONES PROVIDED HERE */
  /* You will get points off if you do not you should at least test each function here */
  printf("TEST CASE 9\nShould only print 2 people in llist2:\n");
  traverse(llist2, print_person);
  printf("Size: %d\n", llist2->size);
  printf("\n");

  /* Edge cases test(Ex. Empty List, single node list test) */
  list* llist3 = create_list();
  printf("TEST CASE 9\nEmpty List test:\n");
  printf("Failed remove_front: %d\n", remove_front(llist3, free_person));
  printf("Failed remove_back: %d\n", remove_back(llist3, free_person));
  printf("None remove_if: %d\n", remove_if(llist3, check_person, free_person));
  printf("should be null: %d\n", front(llist3)==NULL);
  printf("should be null: %d\n", back(llist3)==NULL);
  printf("should be empty: %d\n", is_empty(llist3));
  printf("Size: %d\n", llist3->size);
  traverse(llist3, print_person);
  printf("\n");

  printf("TEST CASE 10\nSize 1 List test:\n");
  push_front(llist3, create_person("King", 1000));
  printf("should not be empty: %d\n", is_empty(llist3));
  printf("remove_front: %d\n", remove_front(llist3, free_person));
  push_front(llist3, create_person("King", 1000));
  printf("remove_back: %d\n", remove_back(llist3, free_person));
  push_front(llist3, create_person("King", 1000));
  printf("remove_if: %d\n", remove_if(llist3, check_person, free_person));
  push_front(llist3, create_person("King", 1000));
  printf("remove_if(Not Pass): %d\n", remove_if(llist3, long_name, free_person));
  printf("Front: should be King: ");
  print_person(front(llist3));
  printf("Back: should be King: ");
  print_person(back(llist3));
  printf("Size: %d\n", llist3->size);
  printf("\n");

 	/* Testing over clean up*/
	empty_list(llist, free_person);
 	free(llist);
	empty_list(llist2, free_person);
	free(llist2);
  empty_list(llist3, free_person);
  free(llist3);

  return 0;
}

