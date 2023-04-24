#include <stdio.h> /*printf*/

#include "d_vector.h"

void PushPopSizeCapacityTest();
void ResizeTest();
void GetAccessTest();

int main()
{
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
	
	elem = DVectorGetAccesToElement(vec, 2);
	
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
