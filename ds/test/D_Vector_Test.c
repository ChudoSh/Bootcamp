/*
Dev: BarSH
Rev: 
Date: 23.4.23
Status: 
*/

#include <stdio.h>

#include "D_Vector.h"

typedef struct dummy
{
	double d;
	int x;
	char a;
}dummy_t;

int main()
{
	dummy_t dum = {0};
	/*int n = 10;
	double d = 98.56465;*/
/******************************************************/	
	dvector_t *vector1 = DVectorCreate(sizeof(dummy_t), 4);
	/*dvector_t *vector2 = StackCreate(2, sizeof(n));
	dvector_t *vector3 = StackCreate(2, sizeof(d));*/
	
	dum.d = 5.5;
	dum.x = 1;
	dum.a = 'a';
	
	
	
	printf("Test for strcut dummy\n");
	
	printf("A vector was created with capacity of %lu\n", DVectorCapacity(vector1));
	
	DVectorPushBack(vector1, &dum);
	
	printf("A value was pushed into the vector\n");
	
	printf("Lets see if it was pushed, 1 means not empty, 0 otherwise: %lu\n", DVectorSize(vector1));
	
	printf("Great its not empty, now lets see what the value of d element in dummy: %f\n", ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->d);
	
	printf("Great its not empty, now lets see what the value of x element in dummy: %d\n", ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->x);
	
	printf("Great its not empty, now lets see what the value of a element in dummy: %c\n", ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->a);
	
	/*Test here for Pop*/
	
	DVectorReserve(vector1, 6);
	
	printf("We've increased the capcity by 4: %lu, but the size is %lu\n", DVectorCapacity(vector1),  DVectorSize(vector1));
	
	DVectorShrink(vector1);
	
	printf("And now back to 2: %lu\n", DVectorSize(vector1));
	
	DVectorDestroy(vector1);
	
	printf("Now we freed the stack, check valgrind for errors\n\n\n\n");
	
	/*
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
	
	printf("Now we freed the stack, check valgrind for errors\n");*/

	return 0;
}

