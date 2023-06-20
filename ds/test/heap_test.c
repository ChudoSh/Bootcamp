/*
Developer: BarSH
Reviewer: MaorH
Status: Approved
Date: 18.6.23
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "heap.h"

static void TestCreatenDestroy();
static void TestInsertSize();
static void TestPop();
static void TestRemove();
static int Compare(const void *a, const void *b);
static int IsMatch(const void *a, const void *b);
static void AutomatedTest(int val, const char *func, int line);

int main()
{
    TestCreatenDestroy();
    TestInsertSize();
    TestPop();
    TestRemove();

    return (0);
}


static void TestCreatenDestroy()
{
    heap_t *heap = HeapCreate(Compare);

    AutomatedTest(HeapIsEmpty(heap), "Create & IsEmpty", __LINE__);
    
    HeapDestroy(heap);
}

static void TestInsertSize()
{
    size_t i = 0;
    int arr[6] = {8, 10, 30, 100 , 45, 7};
    heap_t *heap = HeapCreate(Compare);

    for(i = 0; i < 6; ++i)
    { 
       HeapPush(heap, &arr[i]);
    } 

    AutomatedTest(6 == HeapSize(heap), "Insert & Size", __LINE__);
    AutomatedTest(7 == *(int *)HeapPeek(heap), "Peek", __LINE__);

    HeapDestroy(heap);
}

static void TestPop()
{
    size_t i = 0;
    int arr[6] = {8, 10, 30, 100 , 45, 7};
    heap_t *heap = HeapCreate(Compare);

    for(i = 0; i < 6; ++i)
    { 
       HeapPush(heap, &arr[i]);
    } 

    HeapPop(heap);

    AutomatedTest(5 == HeapSize(heap) && 8 == *(int *)HeapPeek(heap), "Pop", __LINE__);
   
    HeapDestroy(heap);
}

static void TestRemove()
{
    size_t i = 0;
    int arr[6] = {8, 10, 30, 100 , 45, 7};
    heap_t *heap = HeapCreate(Compare);

    for(i = 0; i < 6; ++i)
    { 
       HeapPush(heap, &arr[i]);
    } 

    HeapRemove(heap, &arr[3], IsMatch);
    
    AutomatedTest(5 == HeapSize(heap) && 7 == *(int *)HeapPeek(heap), "Remove", __LINE__);
   
    HeapDestroy(heap);
}

static int Compare(const void *a, const void *b)
{   
    return (*(int *)a - *(int *)b);
}

static int IsMatch(const void *a, const void *b)
{   
    return (*(int *)a == *(int *)b);
}



static void AutomatedTest(int val, const char *func, int line)
{
	char str2[47];
	char temp[100] = {'\0'};
	sprintf(temp, " %d       ", line);
	strncpy(str2, temp, strlen(temp));
	sprintf(temp, "         ");
	sprintf(temp, " %s               ", func);
	strncpy(&str2[6], temp, strlen(temp));
	
	if (val)
	{
		strcpy(&str2[23], "\033[1;32msuccess\033[0m");
	}
	else
	{
		strcpy(&str2[23], "\033[1;31mfail\033[0m");
	}
	
	printf("%s\n", str2);
}

