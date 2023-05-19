/*
Dev: BarSH
Rev: AnnaB
Date: 8.5.23
Status: Approved
*/

#include <stdio.h> /*printf*/
#include <assert.h> /*assert*/
#include <string.h> /* strcpy */

#include "dlist.h"
#include "sortlist.h"


enum
{
	FAIL = 0,
	SUCCESS = 1
};

static int CheckForInsert(void *in_node, const void *cmp_to);
static int MatchInt(void *a, const void *b);
static void Test(int val, const char *func, int line);
static int IsMulti(void *a, const void *b);
static void BasicFunctionTest();
static void FindTest();
static void MergeTest();


static void PrintList(const sort_list_t *list, char *name);

int main()
{		
	BasicFunctionTest();
	FindTest();
	MergeTest();
	
	return (0);
}

static void BasicFunctionTest()
{
	
	int x = 6; 
	int a = 5;
	int b = 7;
	char u = 'A';
	int y = 10;
	
	sort_list_t *list = SortListCreate(CheckForInsert);
	
	sort_iter_t i = {NULL};
	sort_iter_t j = {NULL};
	
	printf("Basic Functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	Test(0 == SortListSize(list), "Size 0", __LINE__);
	Test(SortListIsEmpty(list), "Is empty", __LINE__);
	
	i = SortListBegin(list);
	j = SortListBegin(list);
	
	Test(SortListIsEqual(i,j), "Is equal", __LINE__);
	
	i = SortListInsert(list, &y);
	Test(&y == (int *)(SortListGetData(SortListPrev(i))),
					   "Insert start", __LINE__);
	i = SortListPrev(i);
	i = SortListInsert(list, &b);
	Test(&b == (int *)(SortListGetData(SortListPrev(i))),
					   "Insert start", __LINE__);
	i = SortListPrev(i);
	i = SortListInsert(list, &a);
	Test(&a == (int *)(SortListGetData(SortListPrev(i))), "Insert start", __LINE__);
	i = SortListPrev(i); 
	i = SortListInsert(list, &x);
	Test(&x == (int *)(SortListGetData(SortListPrev(i))), "Insert start", __LINE__);
	i = SortListPrev(i);
	i = SortListInsert(list, &u);
	Test(&u == (char *)(SortListGetData(SortListPrev(i))), "Insert start", __LINE__);
	i = SortListPrev(i);
	
	i = SortListRemove(i);
	i = SortListPrev(i);
	
	Test(y == *(int *)(SortListGetData(i)), "Remove", __LINE__);
	Test(y == *(char *)(SortListPopBack(list)), "PopBack", __LINE__);
	Test(a == *(int *)(SortListPopFront(list)), "PopFront", __LINE__);
	
	
	SortListDestroy(list);
	
	
}

static void FindTest()
{
	sort_list_t *list = SortListCreate(&MatchInt);
	
	int a = 5;
	int b = 3;
	int c = 9;
	int d = 1;
	int s = 666;
	
	

	printf("\vFind tests\n");
	printf("_Line__Name____________Status_\n");
		
	SortListInsert(list, &a);
	SortListInsert(list, &b);	
	SortListInsert(list, &c);	
	SortListInsert(list, &d);	
	/*SortListInsert(list, &s);*/
	
	
	Test(SortListBegin(list).iter == SortListFind(SortListBegin(list), SortListEnd(list), list, &d).iter, "Find found", __LINE__);
	
	Test(SortListEnd(list).iter == SortListFind(SortListBegin(list), SortListEnd(list), list, &s).iter, "Find not", __LINE__);
	
	Test(SortListNext(SortListBegin(list)).iter == SortListFindIf(SortListBegin(list), SortListEnd(list), IsMulti, &b).iter, "Find if found", __LINE__);
	
	Test(SortListEnd(list).iter == SortListFindIf(SortListBegin(list), SortListEnd(list), IsMulti, &s).iter, "Find if not", __LINE__);

	SortListDestroy(list);
}


static void MergeTest()
{
	sort_list_t *dest = SortListCreate(CheckForInsert);
	sort_list_t *src = SortListCreate(CheckForInsert);
	
	int a = 5;
	int b = 3;
	int c = 9;
	int d = 1;
	int e = 100;
	
	int f = 6; 
	int g = 5;
	int h = 7;
	int i = 65;
	int j = 10;

	printf("\vMerge tests\n");
	printf("___Name____________Value_\n");
		
	SortListInsert(dest, &a);
	SortListInsert(dest, &b);	
	SortListInsert(dest, &c);	
	SortListInsert(dest, &d);	
	SortListInsert(dest, &e);
	
	SortListInsert(src, &f);
	SortListInsert(src, &g);	
	SortListInsert(src, &h);	
	SortListInsert(src, &i);	
	SortListInsert(src, &j);
	
	PrintList(dest, "dest");
	PrintList(src, "src");
	
	SortListMerge(dest, src);
	
	PrintList(dest, "dest");
	PrintList(src, "src");

	SortListDestroy(dest);
	SortListDestroy(src);
}


static int MatchInt(void *a, const void *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	return (*(int *)a == *(int *)b);	
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

static int IsMulti(void *a, const void *b)
{
	assert(NULL != a);
	assert(NULL != b);

	return (0 == (*(int *)a % *(int *)b));
}

static int CheckForInsert(void *in_node, const void *cmp_to)
{
	return (*(int *)in_node - *(int *)cmp_to);
}


static void PrintList(const sort_list_t *list, char *name)
{
	sort_iter_t runner = {NULL};
	sort_iter_t end = {NULL};
	
	
	runner = SortListBegin(list);
	end = SortListEnd(list); 
	
	while (runner.iter != end.iter)
	{
		printf("This in a node in list: %s with the value %d\n",name, *((char *)SortListGetData(runner)));
		runner = SortListNext(runner);
	}
	
}

