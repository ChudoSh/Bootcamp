/*
Dev: BarSH
Rev: Michal
Date: 4.5.23
Status: Fixed
*/

#include <stdio.h>

#include "DList.h"

void TestInsertRemoveGetSetNextCount();
void TestIsEqualFind();
static int IntMatch(const void *a, void *b);


int main()
{
	int x = 5; 
	float a = 6;
	double b = 7;
	char *u = "Afasdfasd";
	int y = 10;
	
	iter_t i = NULL;
	iter_t j = NULL;
	
	DList_t *list = DListCreate();
	
	i = DListBegin(list);
	j = DListBegin(list);
	
	DListInsert(i, &x);
	if (x == *((int*)DListGet(i)))
	{
		printf("Test 1 for insert successful!\n");
	}
	else
	{
		printf("Test 1 for insert failed\n");
	}
	i = DListNext(i);
	
	DListInsert(i, &a);
	if (a == *((float*)DListGet(i)))
	{
		printf("Test 2 for insert successful!\n");
	}
	else
	{
		printf("Test 2 for insert failed\n");
	}
	i = DListNext(i);
	
	DListInsert(i, &b);
	if (b == *((double*)DListGet(i)))
	{
		printf("Test 3 for insert successful!\n");
	}
	else
	{
		printf("Test 3 for insert failed\n");
	}
	i = DListNext(i);
	
	DListInsert(i, &u);
	if (u == *((char*)DListGet(i)))
	{
		printf("Test 4 for insert successful!\n");
	}
	else
	{
		printf("Test 4 for insert failed\n");
	}

	
	j = DListNext(j);
	DListSet(j, &y);
	if (y == *((int*)DListGet(j)))
	{
		printf("Test for set successful!\n");
	}
	else
	{
		printf("Test for set insert failed\n");
	}
	
	if (4 == DListCount(list))
	{
		printf("Test for count successful!\n");
	}
	else
	{
		printf("Test for set insert failed\n");
	}

	if (!DListIterIsEqual(DListBegin(list), DListFind(DListBegin(list), DListEnd(list), &y, IntMatch)))
	{
		printf("Test for Find successful!\n");
	}
	else
	{
		printf("Test for set Find failed\n");
	}
	
	TestInsertRemoveGetSetNextCount();
	TestIsEqualFind();
	
	DListDestroy(list);

	return (0);
}

void TestInsertRemoveGetSetNextCount()
{
	DList_t *moo = DListCreate();
	iter_t moop = DListBegin(moo);
	int a = 5;
	char b = 'k';
	char *c = "abcd";
	size_t d = 9;
	
	moop = DListInsert(moop, &a);
	if(&a == DListGet(moop))
	{
		printf("line %d  insert \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  insert \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	moop = DListInsert(moop, &b);
	if(&b == DListGet(moop))
	{
		printf("line %d  insert \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  insert \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	moop = DListInsert(moop, &c);
	if(&c == DListGet(moop))
	{
		printf("line %d  insert \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  insert \033[1;31mfail\033[0m\n", __LINE__);
	}
		
	moop = DListInsert(moop, &d);
	if(&d == DListGet(moop))
	{
		printf("line %d  insert \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  insert \033[1;31mfail\033[0m\n", __LINE__);
	}
		
	moop = DListNext(moop);
	if(&c == DListGet(moop))
	{
		printf("line %d  next   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  next   \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	DListSet(moop, &a);
	if(&a == DListGet(moop))
	{
		printf("line %d  set    \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  set    \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	if(4 == DListCount(moo))
	{
		printf("line %d  count  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  count  \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	moop = DListRemove(moop);
	if(&b == DListGet(moop))
	{
		printf("line %d  remove \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  remove \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	if(3 == DListCount(moo))
	{
		printf("line %d count  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d count  \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	DListDestroy(moo);
}

void TestIsEqualFind()
{
	DList_t *moo = DListCreate();
	iter_t moop = DListBegin(moo);

	int a = 5;
	char b = 'k';
	char *c = "abcd";
	size_t d = 9;
	
	moop = DListInsert(moop, &a);
	moop = DListInsert(DListBegin(moo), &b);
	moop = DListInsert(DListBegin(moo), &c);	
	moop = DListInsert(DListBegin(moo), &d);	
	
	if(moo == DListGet(DListEnd(moo)))
	{
		printf("line %d tail   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d tail   \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	if(DListIterIsEqual(moop,DListFind(DListBegin(moo), DListEnd(moo), &d, IntMatch)))
	{
		printf("line %d find   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d find   \033[1;31mfail\033[0m %d , %d\n", __LINE__, *(int *)DListGet(moop), *(int *)DListGet(DListFind(DListBegin(moo), DListEnd(moo), &a, IntMatch)));
	}
		
	
	DListDestroy(moo);
}

static int IntMatch(const void *a, void *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	return (*(int *)a == *(int *)b);
}
