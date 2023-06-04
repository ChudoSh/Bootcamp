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
    int a = 1;
    int b = 2;
    int c = 3;

    bst_iter_t iter1 = NULL; 
    bst_iter_t iter2 = NULL;
    bst_iter_t iter3 = NULL;
    bst_iter_t iter4 = NULL;

    bst_t *tree = BSTCreate(MatchInt);

    Test(BSTIsEmpty(tree), "IsEmpty",__LINE__);

    BSTInsert(tree, &a);
    BSTInsert(tree, &b);
    BSTInsert(tree, &c);

    Test(1 == *(int *)BSTGetData(BSTBegin(tree)), "Insert",__LINE__);

    iter1 = BSTBegin(tree);
    iter2 = BSTBegin(tree);

    Test(BSTIsSameIter(iter1, iter2), "IsSameIter",__LINE__);

    iter1 = BSTNext(iter1);
    iter1 = BSTNext(iter1);
    Test(3 == *(int *)BSTGetData(iter1), "Next",__LINE__);

    iter1 = BSTPrev(iter1);

    Test(2 == *(int *)BSTGetData(iter1), "Prev",__LINE__);

    iter3 = BSTFind(tree, &b);

    Test(2 == *(int *)BSTGetData(iter3), "Find",__LINE__);

    BSTRemove(iter3);

    iter4 = BSTFind(tree, &b);

    Test(BSTEnd(tree) == iter4, "Remove",__LINE__);

    Test(2 == BSTSize(tree), "Size",__LINE__);

    BSTDestroy(tree);
}

static int MatchInt(const void *a, const void *b)
{
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
