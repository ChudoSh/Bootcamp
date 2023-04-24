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
	dummy_t dum1 = {0};
	dummy_t dum2 = {0};
	dummy_t dum3 = {0};
	dummy_t dum4 = {0};
	/*int n = 10;
	double d = 98.56465;*/
/******************************************************/	
	dvector_t *vector1 = DVectorCreate(sizeof(dummy_t), 4);
	/*dvector_t *vector2 = StackCreate(2, sizeof(n));
	dvector_t *vector3 = StackCreate(2, sizeof(d));*/
	
	dum1.d = 5.5;
	dum1.x = 1;
	dum1.a = 'a';
	
	dum2.d = 8.23;
	dum2.x = 20;
	dum2.a = 'z';
	
	dum3.d = 7.61;
	dum3.x = 8;
	dum3.a = 'T';
	
	dum4.d = 1.9999;
	dum4.x = 1058;
	dum4.a = '!';
	
	
	
	printf("Test for strcut dummy\n");
	
	if (4 ==  DVectorCapacity(vector1))
	{
		printf("Capacity - Success\n");
	}
	else 
	{
		printf("Capacity - Fail\n");
	}
	
	
	DVectorPushBack(vector1, &dum1);
	DVectorPushBack(vector1, &dum2);
	DVectorPushBack(vector1, &dum3);
	DVectorPushBack(vector1, &dum4);
	
	if (5.5 == ((dummy_t*)DVectorGetAccessToElement(vector1, 0))->d && 1 == ((dummy_t*)DVectorGetAccessToElement(vector1, 0))->x && 'a' == ((dummy_t*)DVectorGetAccessToElement(vector1, 0))->a)
	{
		printf("Push & GetAccess test 1 - Success\n");
	}
	else 
	{
		printf("Push & GetAccess test 1 - Fail\n");
	}
	
	if (8.23 == ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->d && 20 == ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->x && 'z' == ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->a)
	{
		printf("Push & GetAccess test 2 - Success\n");
	}
	else 
	{
		printf("Push & GetAccess test 2 - Fail\n");
	}
	
	if (7.61 == ((dummy_t*)DVectorGetAccessToElement(vector1, 2))->d && 8 == ((dummy_t*)DVectorGetAccessToElement(vector1, 2))->x && 'T' == ((dummy_t*)DVectorGetAccessToElement(vector1, 2))->a)
	{
		printf("Push & GetAccess test 3 - Success\n");
	}
	else 
	{
		printf("Push & GetAccess test 3 - Fail\n");
	}
	
	if (1.9999 == ((dummy_t*)DVectorGetAccessToElement(vector1, 3))->d && 1058 == ((dummy_t*)DVectorGetAccessToElement(vector1, 3))->x && '!' == ((dummy_t*)DVectorGetAccessToElement(vector1, 3))->a)
	{
		printf("Push & GetAccess test 4 - Success\n");
	}
	else 
	{
		printf("Push & GetAccess test 4 - Fail\n");
	}
	
	if (4 ==  DVectorSize(vector1))
	{
		printf("Size test - Success\n");
	}
	else 
	{
		printf("Size test - Fail\n");
	}
	
	DVectorPopBack(vector1);
	DVectorPopBack(vector1);
	DVectorPopBack(vector1);
	
	if (1 == DVectorSize(vector1))
	{
		printf("Pop test - Success\n");
	}
	else 
	{
		printf("Pop test - Fail\n");
	}
	
	DVectorReserve(vector1, 8);
	
	if (8 == DVectorCapacity(vector1))
	{
		printf("Increase test - Success\n");
	}
	else 
	{
		printf("Increase test - Fail\n");
	}
	
	DVectorShrink(vector1);
	
	if (1 == DVectorCapacity(vector1))
	{
		printf("Shrink test - Success\n");
	}
	else 
	{
		printf("Shrink test - Fail\n");
	}
	
	DVectorDestroy(vector1);
	
	printf("Destroy test - Check Valgrind\n");
	
	
	return 0;
}

