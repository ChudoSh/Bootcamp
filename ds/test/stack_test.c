/*
Dev: BarSH
Rev: IdoI
Date: 19.4.23
Status: Approved
*/

#include <stdio.h>

#include "stack.h"

typedef struct dummy
{
	double d;
	int x;
	char a;
}dummy_t;

int main()
{
	dummy_t dum = {0};
	int n = 10;
	double d = 98.56465;
/******************************************************/	
	stack_t *my_stack1 = StackCreate(2 ,sizeof(dummy_t));
	stack_t *my_stack2 = StackCreate(2, sizeof(n));
	stack_t *my_stack3 = StackCreate(2, sizeof(d));
	
	dum.d = 5.5;
	dum.x = 1;
	dum.a = 'a';
	
	
	
	printf("Test for strcut dummy\n");
	
	printf("A stack was created with capacity of %lu\n", StackCapacity(my_stack1));
	
	StackPush(my_stack1, &dum);
	
	printf("A value was pushed into the stack\n");
	
	printf("Lets see if it was pushed, 1 means not empty, 0 otherwise: %d\n", StackIsEmpty(my_stack1));
	
	printf("Great its not empty, now lets see what the value of d element in dummy: %f\n", ((dummy_t*)StackPeek(my_stack1))->d);
	
	printf("Great its not empty, now lets see what the value of x element in dummy: %d\n", ((dummy_t*)StackPeek(my_stack1))->x);
	
	printf("Great its not empty, now lets see what the value of a element in dummy: %c\n", ((dummy_t*)StackPeek(my_stack1))->a);
	
	StackPop(my_stack1);
	
	printf("Now we popped the stack, the size should be 0: %lu\n", StackSize(my_stack1));
	
	printf("For capacity test we need to see if the stack still exist, meaning capacity is bigger than 0: %lu\n", StackCapacity(my_stack1));
	
	StackDestroy(my_stack1);
	
	printf("Now we freed the stack, check valgrind for errors\n\n\n\n");

/**********************************************************************/	
	
	printf("Test for int\n");
	
	printf("A stack was created with capacity of %lu\n", StackCapacity(my_stack2));
	
	
	StackPush(my_stack2, &n);
	
	printf("A value was pushed into the stack\n");
	
	printf("Lets see if it was pushed, 1 means not empty, 0 otherwise: %d\n", StackIsEmpty(my_stack2));
	
	printf("Great its not empty, now lets see what the value is: %d\n", *(int*)StackPeek(my_stack2));
	
	StackPop(my_stack2);
	
	printf("Now we popped the stack, the size should be 0: %lu\n", StackSize(my_stack2));
	
	printf("For capacity test we need to see if the stack still exist, meaning capacity is bigger than 0: %lu\n", StackCapacity(my_stack2));
	
	StackDestroy(my_stack2);
	
	printf("Now we freed the stack, check valgrind for errors\n\n\n\n");

/******************************************************************************************/	
	printf("Test for double\n");
	
	
	printf("A stack was created with capacity of %lu\n", StackCapacity(my_stack3));
	
	
	StackPush(my_stack3, &d);
	
	printf("A value was pushed into the stack\n");
	
	printf("Lets see if it was pushed, 1 means not empty, 0 otherwise: %d\n", StackIsEmpty(my_stack3));
	
	printf("Great its not empty, now lets see what the value is: %f\n", *(double*)StackPeek(my_stack3));
	
	StackPop(my_stack3);
	
	printf("Now we popped the stack, the size should be 0: %lu\n", StackSize(my_stack3));
	
	printf("For capacity test we need to see if the stack still exist, meaning capacity is bigger than 0: %lu\n", StackCapacity(my_stack3));
	
	StackDestroy(my_stack3);
	
	printf("Now we freed the stack, check valgrind for errors\n");

	return 0;
}

