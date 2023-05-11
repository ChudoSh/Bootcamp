/*
Dev: BarSH
Rev: Eylon
Status: Approved
Date: 7.5.23
*/

#include <stdio.h>
#include <assert.h>
#include <string.h> /* strcpy */

#include "dlist.h"

void BasicFuncsTest();
void FindMultiFindTest();
void SpliceTest();
void ForEachTest();

enum
{
	FAIL = 0,
	SUCCESS = 1
};

static int IntMatch(void *a, const void *b);
static void PrintList(const dlist_t *list, char *name);

static int AddParam(void *a, void *b);
static void Test(int val, const char *func, int line);

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
	dlist_t *anotherdummy = DListCreate();
	
	i = DListBegin(list);
	j = DListBegin(list);
	
	DListInsert(i, &x);
	i = DListPrev(i);
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
	}
	
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

	DListPushFront(list, &x);

	DListMultiFind(DListBegin(list), DListEnd(list), &IntMatch ,&x, anotherdummy);	
	
	if ((int *)(DListGetData(DListBegin(anotherdummy))) == &x)
	{
		printf("Test for MultiFind successful!\n");
	}
	else
	{
		printf("Test for MultiFind failed\n");
	}
	
	PrintList(anotherdummy, "anotherdummy");
	
	DListPushFront(dummy, &x);
	DListPushFront(dummy, &a);
	DListPushFront(dummy, &b);
	DListPushFront(dummy, &u);
	DListPushFront(dummy, &y);
	
	printf("Before Splice\n");
	PrintList(list, "list");
	PrintList(dummy, "dummy");
	
	DListSplice(DListPrev(DListEnd(list)),DListNext(DListBegin(dummy)), DListPrev(DListEnd(dummy)));
	
	printf("After Splice\n");
	PrintList(list, "list");
	PrintList(dummy, "dummy");

	
	DListPopBack(anotherdummy);
	DListPopBack(anotherdummy);
	if (DListIsEmpty(anotherdummy))
	{
		printf("Test for Popback and IsEmpty successful!\n");
	}
	else
	{
		printf("Test for Popback and IsEmpty failed..\n");
	}
	
	DListPopFront(list);
	
	if (6 == *(int *)(DListGetData(DListBegin(list))))
	{
		printf("Test for PopFront successful!\n");
	}
	else
	{
		printf("Test for PopFront failed..\n");
	}
	
	DListDestroy(list);
	DListDestroy(dummy);
	DListDestroy(anotherdummy);
	
	BasicFuncsTest();
	FindMultiFindTest();
	SpliceTest();
	ForEachTest();

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
void BasicFuncsTest()
{
	dlist_t *moo = DListCreate();
	dlist_iter_t moop = NULL;
	int a = 5;
	char b = 'k';
	char *c = "abcd";
	size_t d = 9;
	int s = 666;
	
	printf("_Line__Name____________Status_\n");
	
	Test(0 == DListSize(moo), "Size 0", __LINE__);
	Test(DListIsEmpty(moo), "Is empty", __LINE__);
	
	DListInsert(DListBegin(moo), &a);
	Test(&a == (int *)(DListGetData(DListBegin(moo))), "Insert start", __LINE__);
	
	DListInsert(DListEnd(moo), &b);	
	DListInsert(DListEnd(moo), &c);	
	DListInsert(DListEnd(moo), &d);	
	
	Test(4 == DListSize(moo), "Size", __LINE__);
	Test(&d == (size_t *)(DListGetData(DListPrev(DListEnd(moo)))), "Insert end", __LINE__);
	
	moop = DListBegin(moo);
	Test(&a == (int *)DListGetData(moop), "Begin", __LINE__);
	
	moop = DListEnd(moo);
	Test(NULL == DListNext(moop), "End", __LINE__);
	
	DListPushFront(moo, &s);
	Test(&s == (int *)DListGetData(DListBegin(moo)), "Push front", __LINE__);
	
	DListPushBack(moo, &s);
	Test(&s == (int *)DListGetData(DListPrev(DListEnd(moo))), "Push back", __LINE__);
	
	moop = DListBegin(moo);
	
	DListRemove(moop);
	Test(&a == (int *)DListGetData(DListBegin(moo)), "Remove", __LINE__);
	
	Test(&s == DListPopBack(moo), "Pop back val", __LINE__);
	Test(&d == (size_t *)DListGetData(DListPrev(DListEnd(moo))), "Pop back", __LINE__);
	
	Test(&a == DListPopFront(moo), "Pop front val", __LINE__);
	Test(&b == (char *)DListGetData(DListBegin(moo)), "Pop front", __LINE__);
	
	DListSetData(DListBegin(moo), &s);
	
	moop = DListBegin(moo);
	Test(DListIsEqual(moop, DListBegin(moo)), "Is equal", __LINE__);
	
	DListDestroy(moo);
}

void FindMultiFindTest()
{
	dlist_t *moo = DListCreate();
	dlist_t *poo = DListCreate();
	dlist_iter_t goop = NULL;
	dlist_iter_t doop = NULL;
	dlist_iter_t hoop = NULL;
	
	int a = 5;
	char b = 'k';
	char *c = "abcd";
	size_t d = 9;
	int s = 666;

	printf("\v_Line__Name____________Status_\n");

	DListInsert(DListBegin(moo), &a);
	DListInsert(DListEnd(moo), &b);	
	DListInsert(DListEnd(moo), &c);	
	DListInsert(DListEnd(moo), &d);	
	
	Test(DListBegin(moo) == DListFind(DListBegin(moo), DListEnd(moo), &IntMatch, &a), "Find found", __LINE__);
	
	Test(DListEnd(moo) == DListFind(DListBegin(moo), DListEnd(moo), &IntMatch, &s), "Find not", __LINE__);
	Test(DListIsEmpty(poo), "Is empty", __LINE__);
	
	DListMultiFind(DListBegin(moo), DListEnd(moo), &IntMatch, &s, poo);
	
	Test(DListIsEmpty(poo), "Multifind none", __LINE__);

	goop = DListPushBack(moo, &s);	
	doop = DListPushBack(moo, &s);	
	hoop = DListPushBack(moo, &s);	
	
	DListMultiFind(DListBegin(moo), DListEnd(moo), &IntMatch, &s, poo);
	
	Test(3 == DListSize(poo), "Multifind 1.1", __LINE__);
	Test(DListGetData(goop) == DListGetData(DListBegin(poo)), "Multifind 1.2", __LINE__);
	Test(DListGetData(doop) == DListGetData(DListNext(DListBegin(poo))), "Multifind 1.3", __LINE__);
	Test(DListGetData(hoop) == DListGetData(DListNext(DListNext(DListBegin(poo)))), "Multifind 1.4", __LINE__);
	
	DListDestroy(poo);
	DListDestroy(moo);
}

void SpliceTest()
{
	dlist_t *moo = DListCreate();
	dlist_t *poo = DListCreate();
	dlist_iter_t goop = NULL;
	dlist_iter_t doop = NULL;
	dlist_iter_t hoop = NULL;
	
	int a = 5;
	char b = 'k';
	char *c = "abcd";
	size_t d = 9;

	printf("\v_Line__Name____________Status_\n");
	
	DListInsert(DListBegin(moo), &a);
	goop = DListInsert(DListEnd(moo), &b);	
	doop = DListInsert(DListEnd(moo), &c);	
	hoop = DListInsert(DListEnd(moo), &d);	

	DListSplice(DListBegin(poo), goop, hoop);
	
	Test(2 == DListSize(poo), "Splice 1.1", __LINE__);
	Test(DListGetData(goop) == DListGetData(DListBegin(poo)), "Splice 1.2", __LINE__);
	Test(DListGetData(doop) == DListGetData(DListPrev(DListEnd(poo))), "Splice 1.3", __LINE__);
	
	Test(2 == DListSize(moo), "Splice 1.4", __LINE__);
	Test(&a == DListGetData(DListBegin(moo)), "Splice 1.5", __LINE__);

	DListDestroy(poo);
	DListDestroy(moo);
}

void ForEachTest()
{
	dlist_t *moo = DListCreate();
	dlist_iter_t moop = NULL;
	int i = 5;
	int a = 5;
	int b = 6;
	int c = 7;
	int d = 8;
	int e = 9;
	
	DListInsert(DListEnd(moo), &a);	
	DListInsert(DListEnd(moo), &b);
	DListInsert(DListEnd(moo), &c);	
	DListInsert(DListEnd(moo), &d);	
	DListInsert(DListEnd(moo), &e);	
	
	DListForEach(DListBegin(moo), DListEnd(moo), &AddParam, &i);
	moop = DListBegin(moo);
	Test(10 == *(int *)DListGetData(moop), "For each 1.1", __LINE__);
	moop = DListNext(moop);
	Test(11 == *(int *)DListGetData(moop), "For each 1.2", __LINE__);
	moop = DListNext(moop);
	Test(12 == *(int *)DListGetData(moop), "For each 1.3", __LINE__);
	moop = DListNext(moop);
	Test(13 == *(int *)DListGetData(moop), "For each 1.4", __LINE__);
	moop = DListNext(moop);
	Test(14 == *(int *)DListGetData(moop), "For each 1.5", __LINE__);

	DListDestroy(moo);
}
static void Test(int val, const char *func, int line)
{
	char str2[47];
	char temp[17] = {'\0'};
	sprintf(temp, " %d       ", line);
	strncpy(str2, temp, strlen(temp));
	sprintf(temp, "         ");
	sprintf(temp, " %s               ", func);
	strncpy(&str2[6], temp, strlen(temp));
	
	if(val)
	{
		strcpy(&str2[23], "\033[1;32msuccess\033[0m");
	}
	else
	{
		strcpy(&str2[23], "\033[1;31mfail\033[0m");
	}
	
	printf("%s\n", str2);
}

static int AddParam(void *a, void *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	*(int *)a += *(int *)b;
	
	return (SUCCESS);
}


