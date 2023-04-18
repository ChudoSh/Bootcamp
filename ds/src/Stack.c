 
#include <stdlib.h>
#include <stdio.h>

#include "../include/Stack.h"

/*struct Stack
{
	size_t size;
	size_t capacity;
	size_t element_size;
	char *sp;
};*/


stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *stack = (stack_t*)(malloc(sizeof(element_size) * sizeof(capacity)));
	
	if (NULL == stack)
	{
		printf("Memory allocation failed");
	}
	
	stack->capacity = capacity;
	stack->size = 0;
	stack->element_size = element_size;
	stack->sp = (char*)stack + sizeof(stack);
	
	return stack;	
}

void StackDestroy(stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	free(my_stack);
	my_stack = NULL;
}

void StackPush(stack_t *my_stack, const void *element)
{
	/*char *push = NULL;*/

	assert(NULL != my_stack);
	assert(NULL != element);
	
	/*push = my_stack->sp;
	++push;*/
	
	my_stack->sp = ((char*)&element);
	my_stack->size += 1;
	/*my_stack->sp = push;	*/
}

void *StackPeek(const stack_t *my_stack)
{
	assert(NULL != my_stack);	

	printf("Peekaboo %p\n", my_stack->sp);
	
}

/*int StackIsEmpty(const stack_t *my_stack)

void StackPop(stack_t *my_stack)

size_t StackSize(const stack_t *my_stack)

size_t StackCapacity(const stack_t *my_stack)*/
