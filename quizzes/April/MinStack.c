#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*memcpy*/
#include <assert.h> /*assert*/

#include "Stack.h"

typedef struct MinStack
{
	stack_t main; 
	stack_t min_val;
}min_t; 

void MinPush(min_t *min_stack, const void* element)
{
	assert(NULL != min_stack);
	assert(NULL != element);
	
	if (*element < StackPeek(min_stack->min_val))
	{
		StackPush(min_stack->min_val, element);
	}
	else
	{
		StackPush(min_stack->min_val, StackPeek(min_stack->min_val));
	}
	StackPush(min_stack->main);	
}

void MinPop(min_t *min_stack)
{
	assert(NULL != min_stack);
	assert(StackIsEmpty(min_stack->main));
	assert(StackIsEmpty(min_stack->min_val));
	
	StackPop(min_stack->main); 
	StackPop(min_stack->min_val);
}

void *GetMin(const min_t *min_stack)
{
	assert(NULL != min_stack);	
	
	return (StackPeek(min_stack->min_val));	
}


