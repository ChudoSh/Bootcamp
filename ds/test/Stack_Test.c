

#include "../include/Stack.h"


int main()
{
	stack_t *my_stack = StackCreate(8, 4);
	
	printf("%lu %lu\n", my_stack->capacity, my_stack->element_size);
	
	StackPush(my_stack, (void*)3);
	/*StackPush(my_stack, (void*)2);*/
	
	StackPeek(my_stack);
	
	StackDestroy(my_stack);
	
	return 0;
}
