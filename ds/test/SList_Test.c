/*
Dev: BarSH
Rev: 
Date: 
Status: 
*/

#include <stdio.h>
#include <assert.h>

#include "SList.h"

void TestInsertRemoveGetSetNextCount();
void TestIsEqualFind();
static int IntMatch(const void *a, void *b);


int main()
{
	int x = 5; 
	float a = 6;
	double b = 7;
	char u = 'A';
	int y = 10;
	
	iter_t i = NULL;
	iter_t j = NULL;
	
	slist_t *list = SListCreate();
	
	i = SListBegin(list);
	j = SListBegin(list);
	
	SListInsert(i, &x);
	if (x == *((int*)SListGet(i)))
	{
		printf("Test 1 for insert successful!\n");
	}
	else
	{
		printf("Test 1 for insert failed\n");
	}
	i = SListNext(i);
	
	SListInsert(i, &a);
	if (a == *((float*)SListGet(i)))
	{
		printf("Test 2 for insert successful!\n");
	}
	else
	{
		printf("Test 2 for insert failed\n");
	}
	i = SListNext(i);
	
	SListInsert(i, &b);
	if (b == *((double*)SListGet(i)))
	{
		printf("Test 3 for insert successful!\n");
	}
	else
	{
		printf("Test 3 for insert failed\n");
	}
	i = SListNext(i);
	
	SListInsert(i, &u);
	if (u == *((char*)SListGet(i)))
	{
		printf("Test 4 for insert successful!\n");
	}
	else
	{
		printf("Test 4 for insert failed\n");
	}

	
	j = SListNext(j);
	SListSet(j, &y);
	if (y == *((int*)SListGet(j)))
	{
		printf("Test for set successful!\n");
	}
	else
	{
		printf("Test for set insert failed\n");
	}
	
	if (4 == SListCount(list))
	{
		printf("Test for count successful!\n");
	}
	else
	{
		printf("Test for set insert failed\n");
	}

	if (!SListIterIsEqual(SListBegin(list), SListFind(SListBegin(list), SListEnd(list), &y, IntMatch)))
	{
		printf("Test for Find successful!\n");
	}
	else
	{
		printf("Test for set Find failed\n");
	}
	
	TestInsertRemoveGetSetNextCount();
	TestIsEqualFind();
	
	SListDestroy(list);

	return (0);
}

void TestInsertRemoveGetSetNextCount()
{
	slist_t *moo = SListCreate();
	iter_t moop = SListBegin(moo);
	int a = 5;
	char b = 'k';
	char *c = "abcd";
	size_t d = 9;
	
	moop = SListInsert(moop, &a);
	if(&a == SListGet(moop))
	{
		printf("line %d  insert \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  insert \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	moop = SListInsert(moop, &b);
	if(&b == SListGet(moop))
	{
		printf("line %d  insert \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  insert \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	moop = SListInsert(moop, &c);
	if(&c == SListGet(moop))
	{
		printf("line %d  insert \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  insert \033[1;31mfail\033[0m\n", __LINE__);
	}
		
	moop = SListInsert(moop, &d);
	if(&d == SListGet(moop))
	{
		printf("line %d  insert \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  insert \033[1;31mfail\033[0m\n", __LINE__);
	}
		
	moop = SListNext(moop);
	if(&c == SListGet(moop))
	{
		printf("line %d  next   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  next   \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	SListSet(moop, &a);
	if(&a == SListGet(moop))
	{
		printf("line %d  set    \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  set    \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	if(4 == SListCount(moo))
	{
		printf("line %d  count  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  count  \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	moop = SListRemove(moop);
	if(&b == SListGet(moop))
	{
		printf("line %d  remove \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d  remove \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	if(3 == SListCount(moo))
	{
		printf("line %d count  \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d count  \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	SListDestroy(moo);
}

void TestIsEqualFind()
{
	slist_t *moo = SListCreate();
	iter_t moop = SListBegin(moo);

	int a = 5;
	char b = 'k';
	char *c = "abcd";
	size_t d = 9;
	
	moop = SListInsert(moop, &a);
	moop = SListInsert(SListBegin(moo), &b);
	moop = SListInsert(SListBegin(moo), &c);	
	moop = SListInsert(SListBegin(moo), &d);	
	
	if(moo == SListGet(SListEnd(moo)))
	{
		printf("line %d tail   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d tail   \033[1;31mfail\033[0m\n", __LINE__);
	}
	
	if(SListIterIsEqual(moop,SListFind(SListBegin(moo), SListEnd(moo), &d, IntMatch)))
	{
		printf("line %d find   \033[1;32msuccess\033[0m\n", __LINE__);
	}
	else
	{
		printf("line %d find   \033[1;31mfail\033[0m %d , %d\n", __LINE__, *(int *)SListGet(moop), *(int *)SListGet(SListFind(SListBegin(moo), SListEnd(moo), &a, IntMatch)));
	}
		
	
	SListDestroy(moo);
}

static int IntMatch(const void *a, void *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	return (*(int *)a == *(int *)b);
}
