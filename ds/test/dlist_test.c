/*
Dev: BarSH
Rev:
Status:
Date
*/

#include <stdio.h>
#include <assert.h>

#include "dlist.h"

static int IntMatch(void *a, const void *b);
static void PrintList(const dlist_t *list, char *name);

int main()
{
	int x = 5; 
	int a = 6;
	int b = 7;
	char u = 'A';
	int y = 10;
	
	dlist_iter_t i = NULL;
	dlist_iter_t j = NULL;
	
	dlist_t *list = DListCreate();
	dlist_t *dummy = DListCreate();
	
	i = DListBegin(list);
	j = DListBegin(list);
	
	DListInsert(i, &x);
	if (x == *((int*)DListGetData(i)))
	{
		printf("Test 1 for DListInsert successful!\n");
	}
	else
	{
		printf("Test 1 for DListInsert failed\n");
	}
	
	DListPushFront(list, &a);
	if (a == *((int*)(DListGetData(DListBegin(list)))))
	{
		printf("Test 1 for PushFront successful!\n");
	}
	else
	{
		printf("Test 1 for PushFront failed\n");
	};
	
	DListPushBack(list, &b);
	if (b == *((int*)(DListGetData(DListPrev(DListEnd(list))))))
	{
		printf("Test 1 for PushBack successful!\n");
	}
	else
	{
		printf("Test 1 for PushBack failed\n");
	}

	
	DListInsert(i, &u);
	i = DListPrev(i);
	if (u == *((char *)DListGetData(i)))
	{
		printf("Test 2 for insert successful!\n");
	}
	else
	{
		printf("Test 2 for insert failed\n");
	}
	
	j = DListPrev(j);
	DListSetData(j, &y);
	if (y == *((int*)DListGetData(j)))
	{
		printf("Test for Set and Get successful!\n");
	}
	else
	{
		printf("Test for Set and Get failed\n");
	}
	
	if (4 == DListSize(list))
	{
		printf("Test for Size successful!\n");
	}
	else
	{
		printf("Test for Size failed\n");
	}


	DListMultiFind(DListBegin(list), DListEnd(list), &IntMatch ,&x, dummy);		
	
	if (*(int *)(DListGetData(DListBegin(dummy))) == x)
	{
		printf("Test for MultiFind successful!\n");
	}
	else
	{
		printf("Test for MultiFind failed\n");
	}
	
	DListPushFront(dummy, &x);
	DListPushFront(dummy, &a);
	DListPushFront(dummy, &b);
	DListPushFront(dummy, &u);
	DListPushFront(dummy, &y);
	
	PrintList(dummy, "dummy");
	PrintList(list, "list");
	
	DListSplice(DListPrev(DListEnd(list)),DListBegin(dummy), DListEnd(dummy));
	
	printf("After Splice\n");
	PrintList(dummy, "dummy");
	PrintList(list, "list");
	
	DListPopBack(dummy);
	if (DListIsEmpty(dummy))
	{
		printf("Test for Popback and IsEmpty successful!\n");
	}
	else
	{
		printf("Test for Popback and IsEmpty failed..\n");
	}
	
	DListPopFront(list);
	
	if (x == *(int *)(DListGetData(DListBegin(list))))
	{
		printf("Test for PopFront successful!\n");
	}
	else
	{
		printf("Test for PopFront failed..\n");
	}
	
	DListDestroy(list);
	DListDestroy(dummy);

	return (0);	
	
}

static int IntMatch(void *a, const void *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	return (*(int *)a == *(int *)b);
}


static void PrintList(const dlist_t *list, char *name)
{
	dlist_iter_t runner = NULL;
	assert(NULL != list);
	
	runner = DListBegin(list);
	
	while (runner != DListEnd(list))
	{
		printf("This in a node in list: %s with the value %d\n",name, *((char *)DListGetData(runner)));
		runner = DListNext(runner);
	}
	
}

