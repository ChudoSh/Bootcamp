#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h> /* size_t, NULL */
#include <assert.h> /*assert*/
#include <stdio.h>

typedef struct Stack stack_t;

struct Stack
{
	size_t size;
	size_t capacity;
	size_t element_size;
	char *sp;
};


/*
Description: Creates a stack type.
arguments:
	*capacity 	 - The maximum variables the stack can hold.
    *element_size - The size of each variable in the stack.
   	return: Retruns the address to the stack.
*/
stack_t *StackCreate(size_t capacity, size_t element_size);

/*
Description: Eliminates a stack type.
arguments:
	*my_stack: A pointer to a stack to be deleted.
   	return: No return value.
*/
void StackDestroy(stack_t *my_stack);


void StackPush(stack_t *my_stack, const void *element);

void StackPop(stack_t *my_stack);

void *StackPeek(const stack_t *my_stack);

int StackIsEmpty(const stack_t *my_stack);

size_t StackSize(const stack_t *my_stack);

size_t StackCapacity(const stack_t *my_stack); 

#endif
