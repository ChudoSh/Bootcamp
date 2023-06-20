/*
Dev: BarSH
Rev: 
Date: 20.6.23
Status: 
*/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcpy */

#include "heap_q.h"

enum RESULT
{
	FAIL = -1,
	SUCCESS = 0
};

static int MatchInt(const void *a, const void *b);
static void Test(int val, const char *func, int line);
static void BasicFunctionTest();
static void EraseAndClearTest();
static int Compare(const void *in_node, const void *cmp_to);

int main()
{		
	BasicFunctionTest();
	EraseAndClearTest();
	
	return (0);
}

static void BasicFunctionTest()
{
    int arr[6] = {6,5,1,7,10,65};
    int i = 0;
	
	pq_t *PartyQuest = PQCreate(Compare);
	
	printf("Basic Functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	Test(PQIsEmpty(PartyQuest), "Is Empty", __LINE__);

    for (i = 0; i < 6; ++i)
    {
	    Test(SUCCESS == PQEnqueue(PartyQuest, &arr[i]), "Enqueue", __LINE__);
    }

    Test(arr[2] == *(int *)(PQPeek(PartyQuest)), "Peek", __LINE__);
	
	Test(6 == PQSize(PartyQuest), "Size 6", __LINE__);
	
	Test(10 == *(int *)PQErase(PartyQuest, &MatchInt, &arr[4]), "Erase", __LINE__);
	
	PQDequeue(PartyQuest);
	PQDequeue(PartyQuest);
	PQDequeue(PartyQuest);

	Test(7 == *(int *)(PQPeek(PartyQuest)), "Dequeue & Peek", __LINE__);
	
	Test(2 == PQSize(PartyQuest), "Size 2", __LINE__);

    PQDequeue(PartyQuest);
    PQDequeue(PartyQuest);
	
	Test(PQIsEmpty(PartyQuest), "IsEmpty", __LINE__);
	
	PQDestroy(PartyQuest);
}

static void EraseAndClearTest()
{

	int x = 6; 
	int a = 5;
	int b = 7;
	char u = 'A';
	int y = 10;
	int g = 1;
	
	pq_t *PartyQuest = PQCreate(Compare);
	
	printf("Clear\n");
	printf("_Line__Name____________Status_\n");
	
	Test(PQIsEmpty(PartyQuest), "Is empty", __LINE__);
	
	PQEnqueue(PartyQuest, &y);
	PQEnqueue(PartyQuest, &b);
	PQEnqueue(PartyQuest, &a);	
	PQEnqueue(PartyQuest, &x);
	PQEnqueue(PartyQuest, &u);
	PQEnqueue(PartyQuest, &g);

	Test(6 == PQSize(PartyQuest), "Size 6", __LINE__);
	
	PQClear(PartyQuest);
	
	Test(PQIsEmpty(PartyQuest), "Clear", __LINE__);
	
	PQDestroy(PartyQuest);
}

static int MatchInt(const void *a, const void *b)
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

static int Compare(const void *in_node, const void *cmp_to)
{
	return (*(int *)in_node - *(int *)cmp_to);
}


