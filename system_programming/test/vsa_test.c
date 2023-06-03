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
void VSATest2();
void VSATest1();

int main()
{
	VSATest2();
	VSATest1();
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
	
	printf("VSA basic functions tests\n");
	printf("_Line__Name____________Status_\n");
	
	largest_chunk = VSAGetLargestChunkAvailable(vsa);
	
	Test(368 == largest_chunk, "Init & Largest", __LINE__);
	
	check = (size_t *)(VSAAlloc(vsa, 50));

	largest_chunk = VSAGetLargestChunkAvailable(vsa);
	
	Test(296 == largest_chunk, "Alloc", __LINE__);

	check2 = (size_t *)(VSAAlloc(vsa, 50));

	largest_chunk = VSAGetLargestChunkAvailable(vsa);
	
	VSAFree(check);
	
	largest_chunk = VSAGetLargestChunkAvailable(vsa);
	
	Test(224 == largest_chunk, "Dfrag", __LINE__);
	
	VSAFree(check2);
	
	largest_chunk = VSAGetLargestChunkAvailable(vsa);

	Test(368 == largest_chunk, "Free", __LINE__);

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
void VSATest1()
{
	void *meep = malloc(56);
	vsa_t *bloop = VSAInit(meep, 56);
	
	Test(24 == VSAGetLargestChunkAvailable(bloop), "Empty lrgst", __LINE__);
	
	VSAAlloc(bloop, 8);
	
	Test(0 == VSAGetLargestChunkAvailable(bloop), "Lrgst available", __LINE__);
	free(meep);
}

void VSATest2()
{
	void *meep = malloc(256);
	vsa_t *bloop = VSAInit(meep, 256);
	
	size_t largest_chunk = 0;
	
	char *b = NULL;
	char *c = NULL;
	char *d = NULL;
	
	Test(224 == VSAGetLargestChunkAvailable(bloop), "Empty lrgst", __LINE__);
	
	VSAAlloc(bloop, 8);
	
	Test(200 == VSAGetLargestChunkAvailable(bloop), "Lrgst available", __LINE__);
	printf("%lu\n", VSAGetLargestChunkAvailable(bloop));
	
	b = VSAAlloc(bloop, 8);
	Test(176 == VSAGetLargestChunkAvailable(bloop), "Lrgst available", __LINE__);
	
	c = VSAAlloc(bloop, 8);
	d = VSAAlloc(bloop, 8);
	
	Test(128 == VSAGetLargestChunkAvailable(bloop), "Lrgst available", __LINE__);
	
	VSAFree(d);
	
	Test(152 == VSAGetLargestChunkAvailable(bloop), "Free", __LINE__);
	
	d = VSAAlloc(bloop, 8);
	VSAFree(b);
	VSAFree(c);
	
	Test(128 == VSAGetLargestChunkAvailable(bloop), "Free", __LINE__);
	
	VSAAlloc(bloop, 8);
	VSAAlloc(bloop, 8);
	VSAAlloc(bloop, 8);
	largest_chunk = VSAGetLargestChunkAvailable(bloop);
	printf("%lu\n",largest_chunk);
	
	Test(56 == VSAGetLargestChunkAvailable(bloop), "Allocate more", __LINE__);
	VSAAlloc(bloop, 8);
	
	free(meep);
}


