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

stack_t *StackCreate(size_t capacity, size_t element_size);
void StackDestroy(stack_t *my_stack);
void StackPush(stack_t *my_stack, const void *element);
void *StackPeek(const stack_t *my_stack);
void StackPop(stack_t *my_stack);
int IsBalancedParanthesses(char *str, size_t size);
int StackIsEmpty(const stack_t *my_stack);

int main()
{
	char *str = "[[]";	
	
	if (0  == IsBalancedParanthesses(str, sizeof(str)))
	{
		printf("Success\n");
	}
	else
	{
		printf("fail\n");
	}

	
	return (0);
}

int IsBalancedParanthesses(char *str, size_t size)
{
	char LUT[256] = {0};
	stack_t *stack = NULL; 
	
	assert(NULL != str);
	
	stack = StackCreate(size, sizeof(char));
	
	while ('\0' != *str)
	{
		if ('(' == *str || '{' == *str || '[' == *str)
		{
			StackPush(stack, &(*str));
		}
		
		else
		{
			switch (*str)
			{	
				case (')'):			
					if (*((char*)StackPeek(stack)) != '(')
					{
						return (0);
					}
					StackPop(stack);
					break;
					
				case ('}'):
					if (*((char*)StackPeek(stack)) != '{')
					{
						return (0);
					}
					StackPop(stack);
					break;
					
				case (']'):
					if (*((char*)StackPeek(stack)) != '[')
					{
						return (0);
					}
					StackPop(stack);
					break;
					
				default:
					break;	 
			}
		}	
		++(str);	
	}
	
	if (StackIsEmpty(stack))
	{
		StackDestroy(stack);
		return  (1);
	}
	else
	{
		StackDestroy(stack);
		return  (0);
	}
	
			
}

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
