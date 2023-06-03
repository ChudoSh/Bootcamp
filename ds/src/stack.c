/*
Dev: BarSH
Rev: IdoI
Date: 19.4.23
Status: Approved
*/ 

#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*memcpy*/
#include <assert.h> /*assert*/

#include "stack.h"


struct Stack
{
	size_t size;
	size_t capacity;
	size_t element_size;
	char *sp;
};

/*Creates the stack*/
stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *stack = (stack_t*)(malloc((element_size * capacity) + sizeof(stack_t)));
	
	if (NULL == stack)
	{
		return NULL;
	}
	
	stack->capacity = capacity;
	stack->size = 0;
	stack->element_size = element_size;
	stack->sp = (char*)stack + sizeof(stack);
	
	return (stack);	
}

/*Erases the stacks*/
void StackDestroy(stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	free(my_stack);
	my_stack = NULL;
}

/*Adds an element to the stack*/
void StackPush(stack_t *my_stack, const void *element)
{
	assert(NULL != my_stack);
	assert(NULL != element);
	assert(my_stack->capacity > my_stack->size);
	
	memcpy(my_stack->sp, element, my_stack->element_size);
	
	my_stack->sp += my_stack->element_size;
	++my_stack->size;
}

/*Gets the top element of the stack*/
void *StackPeek(const stack_t *my_stack)
{
	assert(NULL != my_stack);	
	
	return ((void*)((my_stack->sp) - (my_stack->element_size)));	
}

/*Checks is the stack is empty*/
int StackIsEmpty(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return (0 != my_stack->size);
}

/*Pops the stack*/
void StackPop(stack_t *my_stack)
{
	assert(NULL != my_stack);
	assert(StackIsEmpty(my_stack));
	
	my_stack->sp -= my_stack->element_size;
	--my_stack->size;
}

/*Reveales the stack size*/
size_t StackSize(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return (my_stack->size);
}

/*Reveales the stack capacity*/
size_t StackCapacity(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return (my_stack->capacity);
}
