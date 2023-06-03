/*
Dev: BarSH
Rev: LeonG
Date: 17.5.23
Status: Approved
*/

#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strcpy */

#include "pqueue.h"



enum RESULT
{
	FAIL = 0,
	SUCCESS = 1
};

static int MatchInt(const void *a, const void *b);
static void Test(int val, const char *func, int line);
static void BasicFunctionTest();
static void EraseAndClearTest();
static int CheckForEnqueue(const void *in_node, const void *cmp_to);

int main()
{		
	BasicFunctionTest();
	EraseAndClearTest();
	
	return (0);
}

static void BasicFunctionTest()
{
	int x = 6; 
	int a = 5;
	int b = 7;
	char u = 'A';
	int y = 10;
	int g = 1;
	
	pq_t *PartyQuest = PQCreate(CheckForEnqueue);
	
	printf("Basic Functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	Test(0 == PQSize(PartyQuest), "Size 0", __LINE__);
	Test(PQIsEmpty(PartyQuest), "Is empty", __LINE__);
	
	PQEnqueue(PartyQuest, &y);
	Test(&y == (int *)(PQPeek(PartyQuest)),"Enqueue & Peek", __LINE__);
	PQEnqueue(PartyQuest, &b);
	Test(&y == (int *)(PQPeek(PartyQuest)),"Enqueue & Peek", __LINE__);
	PQEnqueue(PartyQuest, &a);
	Test(&y == (int *)(PQPeek(PartyQuest)), "Enqueue & Peek", __LINE__); 	
	PQEnqueue(PartyQuest, &x);
	Test(&y == (int *)(PQPeek(PartyQuest)), "Enqueue & Peek", __LINE__);
	PQEnqueue(PartyQuest, &u);
	Test(&u == (char *)(PQPeek(PartyQuest)), "Enqueue & Peek", __LINE__);
	
	Test(5 == PQSize(PartyQuest), "Size 5", __LINE__);
	
	Test(0 == PQErase(PartyQuest, &MatchInt, &b), "Erase exist", __LINE__);
	
	PQDequeue(PartyQuest);
	Test(u == *(char *)(PQPeek(PartyQuest)), "Dequeue & Peek", __LINE__);
	PQDequeue(PartyQuest);
	Test(u == *(char *)(PQPeek(PartyQuest)), "Dequeue & Peek", __LINE__);
	PQDequeue(PartyQuest);
	Test(u == *(char *)(PQPeek(PartyQuest)), "Dequeue & Peek", __LINE__);
	
	Test(1 == PQSize(PartyQuest), "Size 1", __LINE__);
	
	Test(u == *(char *)(PQDequeue(PartyQuest)), "Dequeue & Peek", __LINE__);
	
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
	
	pq_t *PartyQuest = PQCreate(CheckForEnqueue);
	
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

static int CheckForEnqueue(const void *in_node, const void *cmp_to)
{
	return (*(int *)in_node - *(int *)cmp_to);
}


