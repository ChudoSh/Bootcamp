/*
Dev: BarSH
Rev: EtaiSH
Date: 25.4.23
Status: Fixing 
*/

#include <stdio.h>

#include "D_Vector.h"

typedef struct dummy
{
	double d;
	int x;
	char a;
}dummy_t;

void PushPopSizeCapacityTest();
void ResizeTest();
void GetAccessTest();

int main()
{

	dummy_t dum1 = {0};
	dummy_t dum2 = {0};
	dummy_t dum3 = {0};
	dummy_t dum4 = {0};
		
	dvector_t *vector1 = DVectorCreate(sizeof(dummy_t), 4);
	
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
	
	if (dum1.d == ((dummy_t*)DVectorGetAccessToElement(vector1, 0))->d && dum1.x == ((dummy_t*)DVectorGetAccessToElement(vector1, 0))->x && dum1.a == ((dummy_t*)DVectorGetAccessToElement(vector1, 0))->a)
	{
		printf("Push & GetAccess test 1 - Success\n");
	}
	else 
	{
		printf("Push & GetAccess test 1 - Fail\n");
	}
	
	if (dum2.d == ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->d && dum2.x == ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->x && dum2.a == ((dummy_t*)DVectorGetAccessToElement(vector1, 1))->a)
	{
		printf("Push & GetAccess test 2 - Success\n");
	}
	else 
	{
		printf("Push & GetAccess test 2 - Fail\n");
	}
	
	if (dum3.d == ((dummy_t*)DVectorGetAccessToElement(vector1, 2))->d && dum3.x == ((dummy_t*)DVectorGetAccessToElement(vector1, 2))->x && dum3.a == ((dummy_t*)DVectorGetAccessToElement(vector1, 2))->a)
	{
		printf("Push & GetAccess test 3 - Success\n");
	}
	else 
	{
		printf("Push & GetAccess test 3 - Fail\n");
	}
	
	if (dum4.d == ((dummy_t*)DVectorGetAccessToElement(vector1, 3))->d && dum4.x == ((dummy_t*)DVectorGetAccessToElement(vector1, 3))->x && dum4.a == ((dummy_t*)DVectorGetAccessToElement(vector1, 3))->a)
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
	
	PushPopSizeCapacityTest();
	ResizeTest();
	GetAccessTest();
	
	return 0;
}

void PushPopSizeCapacityTest()
{
	dvector_t *vec = NULL;
	const int a = 15;
	const int b = 30;
	const int c = 1;
	const int d = 3;
	vec = DVectorCreate(4, 2);
	
	DVectorPushBack(vec, &a);	
	DVectorPushBack(vec, &b);
	DVectorPushBack(vec, &c);
	DVectorPushBack(vec, &d);
	if((4 == DVectorCapacity(vec)) && (4 == DVectorSize(vec)))
	{
		printf("line %d  PushBack  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  PushBack  \033[1;31mfail\033\n", __LINE__);
	}
	
	DVectorPushBack(vec, &d);
	if((8 == DVectorCapacity(vec)) && (5 == DVectorSize(vec)))
	{
		printf("line %d  PushBack  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  PushBack  \033[1;31mfail\033\n", __LINE__);
	}
		
	DVectorPushBack(vec, &a);
	DVectorPushBack(vec, &b);
	DVectorPushBack(vec, &c);
	DVectorPushBack(vec, &d);
	if((16 == DVectorCapacity(vec)) && (9 == DVectorSize(vec)))
	{
		printf("line %d  PushBack  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  PushBack  \033[1;31mfail\033\n", __LINE__);
	}
	DVectorPushBack(vec, &d);
	
	DVectorPopBack(vec);
	if((16 == DVectorCapacity(vec)) && (9 == DVectorSize(vec)))
	{
		printf("line %d  PopBack   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  PopBack   \033[1;31mfail\033\n", __LINE__);
	}
	DVectorPopBack(vec);
	
	DVectorPopBack(vec);
	
	DVectorPopBack(vec);
	
	DVectorPopBack(vec);
	
	DVectorPopBack(vec);
	if((8 == DVectorCapacity(vec)) && (4 == DVectorSize(vec)))
	{
		printf("line %d  PopBack   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  PopBack   \033[1;31mfail\033\n", __LINE__);
	}
	DVectorPopBack(vec);
		
	DVectorPopBack(vec);
	if((4 == DVectorCapacity(vec)) && (2 == DVectorSize(vec)))
	{
		printf("line %d  PopBack   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  PopBack   \033[1;31mfail\033\n", __LINE__);
	}
	DVectorDestroy(vec);
}

void ResizeTest()
{
	dvector_t *vec = NULL;

	const int d = 3;
	vec = DVectorCreate(4, 2);
	if((2 == DVectorCapacity(vec)) && (0 == DVectorSize(vec)))
	{
		printf("line %d Create    \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d Create    \033[1;31mfail\033\n", __LINE__);
	}
	
	DVectorPushBack(vec, &d);
	if((2 == DVectorCapacity(vec)) && (1 == DVectorSize(vec)))
	{
		printf("line %d PushBack  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d PushBack  \033[1;31mfail\033\n", __LINE__);
	}
	
	DVectorReserve(vec, 30);
	if((30 == DVectorCapacity(vec)) && (1 == DVectorSize(vec)))
	{
		printf("line %d Reserve   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d Reserve   \033[1;31mfail\033\n", __LINE__);
	}
	
	DVectorPushBack(vec, &d);
	DVectorPushBack(vec, &d);
	DVectorPushBack(vec, &d);

	if((30 == DVectorCapacity(vec)) && (4 == DVectorSize(vec)))
	{
		printf("line %d PushBack  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d PushBack  \033[1;31mfail\033\n", __LINE__);
	}
	
	DVectorShrink(vec);
	if((5 == DVectorCapacity(vec)) && (4 == DVectorSize(vec)))
	{
		printf("line %d Shrink    \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d Shrink    \033[1;31mfail\033\n", __LINE__);
	}
	
	DVectorDestroy(vec);
}

void GetAccessTest()
{
	dvector_t *vec = NULL;
	int *elem = NULL;

	const int a = 15;
	const int b = 30;
	const int c = 1;

	vec = DVectorCreate(4, 2);
	
	DVectorPushBack(vec, &a);
	DVectorPushBack(vec, &b);
	DVectorPushBack(vec, &c);
	
	elem = (int*)DVectorGetAccessToElement(vec, 2);
	
	if(1 == *elem)
	{
		printf("line %d GetAccess \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d GetAccess \033[1;31mfail\033\n", __LINE__);
	}
	
	*elem = -5;
	
	if(-5 == *elem)
	{
		printf("line %d GetAccess value change \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d GetAccess value change \033[1;31mfail\033\n", __LINE__);
	}
	DVectorDestroy(vec);
}
