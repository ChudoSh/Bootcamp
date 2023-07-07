
#include <stdio.h>

#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*memcpy*/
#include <assert.h> /*assert*/


typedef struct Stack
{
	size_t size;
	size_t capacity;
	size_t element_size;
	char *sp;
}stack_t;

/*Creates the stack*/
stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *stack = NULL;

	assert(0 < capacity);
	assert(0 < element_size);

	stack = (stack_t*)(malloc((element_size * capacity) + sizeof(stack_t)));
	if (NULL == stack)
	{
		return (NULL);
	}
	
	stack->capacity = capacity;
	stack->size = 0;
	stack->element_size = element_size;
	stack->sp = (char *)(stack + 1);

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
	assert(my_stack->size != my_stack->capacity);
	
	memcpy(my_stack->sp, element, my_stack->element_size);

	my_stack->sp += my_stack->element_size;
	++(my_stack->size);	

}

/*Checks is the stack is empty*/
int StackIsEmpty(const stack_t *my_stack)
{
	assert(NULL != my_stack);
	
	return (0 == my_stack->size);
}

/*Pops the stack*/
void StackPop(stack_t *my_stack)
{
	assert(NULL != my_stack);
	assert(!StackIsEmpty(my_stack));
	
	my_stack->sp -= my_stack->element_size;
	--(my_stack->size);
}

/*Gets the top element of the stack*/
void *StackPeek(const stack_t *my_stack)
{
	assert(NULL != my_stack);	
	
	return ((void*)((my_stack->sp) - (my_stack->element_size)));	
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

void StackSort(stack_t *stack);
void SortCurrent(stack_t *stack, void *current);

/*============================================================================*/

int main()
{
    stack_t *stack = StackCreate(7, 4);
    int i = 0;
    int arr[10] = {10, -8 ,15, -9,-11, 454, 55};
    
    for (i = 0; i < 7; ++i)
    {
        StackPush(stack, &arr[i]);
        printf("%d\n", *(int *)StackPeek(stack));
    }

    StackSort(stack);

    for (i = 0; i < 7; ++i)
    {
        printf("%d\n", *(int *)StackPeek(stack));
        StackPop(stack);
    }

    StackDestroy(stack);

    return (0);
}

void StackSort(stack_t *stack)
{
    void *current = NULL;
    
    if (!StackIsEmpty(stack))
    {
        current = StackPeek(stack);
        StackPop(stack);

        StackSort(stack);

        SortCurrent(stack, current);
    }
}

void SortCurrent(stack_t *stack, void *current)
{
    void *save = NULL;

    if (StackIsEmpty(stack) || *(int *)StackPeek(stack) < *(int *)current)
    {
        StackPush(stack , current);
        return;
    }

    save = StackPeek(stack);
    StackPop(stack);

    SortCurrent(stack, current); 

    StackPush(stack, save);  
}