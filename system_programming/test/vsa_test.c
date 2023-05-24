/*
Dev: BarSH
Rev: EtaiSH
Status: Test impl.
Date: 24.5.23
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vsa.h"

static void Test(int val, const char *func, int line);
static void VSATest();

int main()
{
	VSATest();
	return (0);
}

static void VSATest()
{
	size_t *check = NULL;
	size_t *check2 = NULL;
	size_t largest_chunk = 0;
	size_t *test = (size_t *)malloc(400);
	vsa_t *vsa = VSAInit(test, 400);
	
	printf("FSA basic functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	largest_chunk = VSAGetLargestChunkAvailable(vsa);
	
	Test(384 == largest_chunk, "Init & Largest", __LINE__);
	
	check = (size_t *)(VSAAlloc(vsa, 50));

	largest_chunk = VSAGetLargestChunkAvailable(vsa);
	
	Test(312 == largest_chunk, "Alloc", __LINE__);

	check2 = (size_t *)(VSAAlloc(vsa, 50));

	largest_chunk = VSAGetLargestChunkAvailable(vsa);
	
	VSAFree(check);
	VSAFree(check2);
	
	largest_chunk = VSAGetLargestChunkAvailable(vsa);
	
	Test(384 == largest_chunk, "Free", __LINE__);

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


