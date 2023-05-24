/*
Dev: BarSH
Rev: 
Status: Test impl.
Date: 19.5.23
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsa.h"

static void Test(int val, const char *func, int line);
static void FSATest();

int main()
{
	FSATest();
	return (0);
}

static void FSATest()
{
	size_t *check = NULL;
	size_t *check2 = NULL;
	size_t free_amount = 0;
	size_t alloc_size = FSASuggestSize(200, sizeof(size_t));
	size_t *test = (size_t *)malloc(alloc_size);
	fsa_t *fsa = FSAInit(test, alloc_size, sizeof(size_t));
	
	printf("FSA basic functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	free_amount = FSACountFree(fsa);
	
	Test(200 == free_amount, "Create & Count", __LINE__);
	
	check = (size_t *)FSAAlloc(fsa);
	*check = 8;
	free_amount = FSACountFree(fsa);
	
	Test(199 == free_amount, "Alloc", __LINE__);
	
	check2 = (size_t *)FSAAlloc(fsa); 
	*check2 = 10;
	FSAFree(fsa ,(void *)check2);
	
	Test(199 == free_amount, "Free", __LINE__);
	
	free(test);

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


