/*
Dev: BarSH
Rev: 
Date: .6.23
Status: 
*/

#include <assert.h>/*assert*/
#include <stdio.h>/*printf*/
#include <stdlib.h>/*free*/
#include <string.h> /*strcpy*/


#include "bst.h"

static void Test(int val, const char *func, int line);

static int MatchInt(const void *a, const void *b);
void TestTree();


int main()
{
    TestTree();

    return (0);
}

void TestTree()
{
    bst_t *tree = BSTCreate(MatchInt);

    Test(BSTIsEmpty(tree), "IsEmpty & Size",__LINE__);

    BSTDestroy(tree);
}

static int MatchInt(const void *a, const void *b)
{
	assert(NULL != a);
	assert(NULL != b);
	
	return (*(int *)a - *(int *)b);	
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
