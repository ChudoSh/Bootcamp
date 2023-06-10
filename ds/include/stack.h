/*
Dev: BarSH
Rev: IdoI
Date: 19.4.23
Status: Approved
*/

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>/*size_t*/

typedef struct Stack stack_t;

/*
Description: Creates a stack type.
Arguments:
	*capacity 	 - The maximum variables the stack can hold.
    *element_size - The size of each variable in the stack.
Return value: 
	Retruns the address to the stack.
Complexity: 
	Time 0(1) / Space 0(n).
*/
stack_t *StackCreate(size_t capacity, size_t element_size);

/*
Description: Eliminates a stack type.
Arguments:
	*my_stack: A valid pointer to a stack to be deleted.
Return value: 
	No return value.
Complexity: 
	Time 0(1) / Space 0(1).
*/
void StackDestroy(stack_t *my_stack);

/*
Description: Adds an element to the stack.
Arguments:
	*my_stack: A valid pointer to a stack.
	*element: A valid pointer to a constant element.
Return value: 
	No return value.
Complexity: 
	Time 0(1) / Space 0(1).
*/
void StackPush(stack_t *my_stack, const void *element);

/*
Description: Removes an element from the stack.
Arguments:
	*my_stack: A valid pointer to a stack to be deleted.
Return value: 
	No return value.
Complexity: 
	Time 0(1) / Space 0(1).
*/
void StackPop(stack_t *my_stack);

/*
Description: Shows the value of the top element of the stack.
Arguments:
	*my_stack: A valid pointer to a stack.
Return value:
	No return value.
Complexity:
	Time 0(1) / Space 0(1).
*/
void *StackPeek(const stack_t *my_stack);

/*
Description: Indicates if a stack is empty.
Arguments:
	*my_stack: A valid pointer to a constant stack.
Return value:
	0 if the stack is empty, 1 otherwise.
Complexity:
	Time 0(1) / Space 0(1).
*/
int StackIsEmpty(const stack_t *my_stack);

/*
Description: Retrieves the current value of the stack size.
Arguments:
	*my_stack: A valid pointer to a constant stack.
Return value:
	The size of the stack.
Complexity:
	Time 0(1) / Space 0(1).
*/
size_t StackSize(const stack_t *my_stack);

/*
Description: Retrieves the capacity value of the stack.
Arguments:
	*my_stack: A valid pointer to a constant stack.
Return value:
	The capacity of the stack..
Complexity:
	Time 0(1) / Space 0(1).
*/
size_t StackCapacity(const stack_t *my_stack); 

#endif /*__STACK_H__*/
