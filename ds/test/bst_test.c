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

#define SUCCESS (0)

enum
{
    FALSE = 0,
    TRUE
};
const size_t rand_seed = 10;

#define NORM_COEFFICIENT (1000)

static void Test(int val, const char *func, int line);


static void TestCreateDestroy(const char *announce);
static void TestNext(const char *announce);
static void TestSize(const char *announce);
static void TestFind(const char *announce);
static void TestRemove(const char *announce);
static void TestRemoveWithSeedTwo(const char *announce);
static void TestForEach(const char *announce);

static void InitilizeList(int *arr, size_t size, size_t seed);
static void PrintSuccess();
static void PrintFailure();
static void CheckSuccessOrFailure(const char * message, int to_check);
static void FindMinMaxIndexes(int *arr, size_t size, size_t *max_index, size_t *min_index);
static int AddParam(void *in_node, void *param);
static void DuplicateArrays(int *arr1, int *arr2, size_t size);
static int IsArraysSame(int *arr1, int *arr2, size_t size, int param);

int CompareInts(const void *in_tree, const void *param);

static int MatchInt(const void *a, const void *b);
void TestTree();


int main()
{
    TestTree();
    TestCreateDestroy("~~~Create Destroy test~~~");
    TestNext("~~~BstNext test~~~");
    TestSize("~~~BSTSize test~~~");
    TestFind("~~~BSTFind test~~~");
    TestRemove("~~~BST remove test(general)~~~");
    TestRemoveWithSeedTwo("~~~BST remove test(seed 2) maximum value at root~~~");
    TestForEach("~~~BST ForEach test~~~");

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

static void TestCreateDestroy(const char *message)
{
    bst_t *tree = NULL;
    tree = BSTCreate(&CompareInts);

    printf("%s \n", message);

    CheckSuccessOrFailure("If no valgrind", TRUE);

    BSTDestroy(tree);
}

static void TestNext(const char *message)
{
    bst_t *tree = NULL;
    int arr[3] = {3, 5, 1};
    tree = BSTCreate(&CompareInts);

    printf("%s \n", message);


    BSTInsert(tree, arr);
    BSTInsert(tree, arr + 1);
    BSTInsert(tree, arr + 2);

    CheckSuccessOrFailure("Testing Begin", arr + 2 == (int *)BSTGetData((BSTBegin(tree))));
    CheckSuccessOrFailure("Testing Next", arr == (int *)BSTGetData(BSTNext(BSTBegin(tree))));
    CheckSuccessOrFailure("Testing Next Next", arr + 1 == (int *)BSTGetData(BSTNext(BSTNext(BSTBegin(tree)))));
    CheckSuccessOrFailure("Testing Next Next Next", BSTIsSameIter(BSTEnd(tree), BSTNext(BSTNext(BSTNext(BSTBegin(tree))))));

    BSTDestroy(tree);
}

static void TestSize(const char *message)
{
    bst_t *tree = NULL;
    int arr[30] = {0};
    size_t size = sizeof(arr)/sizeof(int);
    size_t i = 0;
    size_t half = size/2;

    printf("%s \n", message);

    tree = BSTCreate(&CompareInts);
    InitilizeList(arr, size, rand_seed);

    for(i = 0; i < size - half; ++i)
    {
        BSTInsert(tree, arr + i);
    }

    CheckSuccessOrFailure("Testing Size, first insert set", size - half 
                                                                == BSTSize(tree));
  
    for( ; i < size; ++i)
    {
        BSTInsert(tree, arr + i);
    }

    CheckSuccessOrFailure("Testing Size, Second insert set", size == BSTSize(tree));

    BSTDestroy(tree);
}

static void TestFind(const char *message)
{
    bst_t *tree = NULL;
    int arr[30] = {0};
    size_t size = sizeof(arr)/sizeof(int);
    size_t half = size/2;
    size_t i = 0;
    bst_iter_t iter = NULL;

    printf("%s \n", message);


    tree = BSTCreate(&CompareInts);
    InitilizeList(arr, size, rand_seed);

    for(i = 0; i < half ; ++i)
    {
        iter = BSTInsert(tree, arr + i);
    }

    for(i = half; i < size - 1 ; ++i)
    {
        BSTInsert(tree, arr + i);
    }

    CheckSuccessOrFailure("Test find(in tree)", 
                                    BSTIsSameIter(BSTFind(tree, arr + half -1), iter));

    CheckSuccessOrFailure("Test find(not in tree)", 
                                    BSTIsSameIter(BSTFind(tree, arr + size - 1), BSTEnd(tree)));

    BSTDestroy(tree);
}

static void TestRemove(const char *message)
{
    bst_t *tree = NULL;
    int arr[16] = {0};
    size_t min_index = 0;
    size_t max_index = 0;
    size_t size = sizeof(arr)/sizeof(int);
    size_t half = size/2;
    size_t i = 0;
    bst_iter_t iter[16] = {NULL};

    printf("%s \n", message);


    tree = BSTCreate(&CompareInts);
    InitilizeList(arr, size, rand_seed);
    FindMinMaxIndexes(arr, size, &max_index, &min_index);

    for(i = 0; i < size ; ++i)
    {
        *(iter + i) = BSTInsert(tree, arr + i);
        if (BSTIsSameIter(*(iter + i), BSTEnd(tree)))
        {
            printf("Error\n");
            return;
        }
    }

    for(i = 0; i < half ; ++i)
    {
        BSTRemove(BSTBegin(tree));
    }

    CheckSuccessOrFailure("Test Remove with find(is removed)", 
                                    BSTIsSameIter(BSTFind(tree, arr + min_index), BSTEnd(tree)));

    CheckSuccessOrFailure("Test Remove with size", half == BSTSize(tree));

    CheckSuccessOrFailure("Test Remove hasnt changed other items", 
                                    (arr + max_index) == BSTGetData(BSTFind(tree, arr + max_index)));

    BSTDestroy(tree);
}

static void TestRemoveWithSeedTwo(const char *message)
{
    bst_t *tree = NULL;
    int arr[16] = {0};
    size_t min_index = 0;
    size_t max_index = 0;
    size_t size = sizeof(arr)/sizeof(int);
    size_t half = size/2;
    size_t i = 0;
    bst_iter_t iter[16] = {NULL};

    printf("%s \n", message);

    tree = BSTCreate(&CompareInts);
    InitilizeList(arr, size, 2);
    FindMinMaxIndexes(arr, size, &max_index, &min_index);

    for(i = 0; i < size ; ++i)
    {
        *(iter + i) = BSTInsert(tree, arr + i);
        if (BSTIsSameIter(*(iter + i), BSTEnd(tree)))
        {
            printf("Error\n");
            return;
        }
    }

    for(i = 0; i < half ; ++i)
    {
        BSTRemove(BSTBegin(tree));
    }

    CheckSuccessOrFailure("Test Remove with find(is removed)", 
                                    BSTIsSameIter(BSTFind(tree, arr + min_index), BSTEnd(tree)));

    CheckSuccessOrFailure("Test Remove with size", half == BSTSize(tree));

    CheckSuccessOrFailure("Test Remove hasnt changed other items", 
                                    (arr + max_index) == BSTGetData(BSTFind(tree, arr + max_index)));

    BSTDestroy(tree);
}

static void TestForEach(const char *message)
{
    bst_t *tree = NULL;
    int arr[30] = {0};
    int arr2[30] = {0};
    size_t size = sizeof(arr)/sizeof(int);
    size_t i = 0;
    int param = 5;
    bst_iter_t iter = NULL;

    printf("%s \n", message);

    tree = BSTCreate(&CompareInts);
    InitilizeList(arr, size, rand_seed);
    DuplicateArrays(arr, arr2, size);

    for(i = 0; i < size ; ++i)
    {
        iter = BSTInsert(tree, arr + i);
        if (BSTIsSameIter(iter, BSTEnd(tree)))
        {
            printf("Error\n");
            return;
        }
    }


    CheckSuccessOrFailure("Test return of foreach with find(is removed)", SUCCESS
                             == BSTForEach(BSTBegin(tree), BSTEnd(tree), &AddParam, &param));

    CheckSuccessOrFailure("Test Remove hasnt changed other items", IsArraysSame(arr, arr2, size, param));

    BSTDestroy(tree);
}




/*Test Utilities========================*/
static void InitilizeList(int *arr, size_t size, size_t seed)
{
    size_t i = 0;

    srand(seed);

    for(i = 0; i < size; ++i)
    {
        *(arr + i) = rand() % (2 * NORM_COEFFICIENT) - rand() % (2 * NORM_COEFFICIENT);
    }
}

static void PrintSuccess()
{
  	printf("\033[0;32m");
	printf("Success");
  	printf("\033[0m");
  	printf("\n");
}

static void PrintFailure()
{
	printf("\033[1;31m");
	printf("Failure");
  	printf("\033[0m");
  	printf("\n");
}

static void CheckSuccessOrFailure(const char * message, int to_check)
{
    printf("%s :", message);
	to_check ? PrintSuccess() : PrintFailure();
}

static void FindMinMaxIndexes(int *arr, size_t size, size_t *max_index, size_t *min_index)
{
    size_t i = 0;

    for(i = 0; i < size; ++i)
    {
        if(arr[i] > arr[*max_index])
        {
            *max_index = i;
        }
        else if(arr[i] < arr[*min_index])
        {
            *min_index = i;
        }
    }
}

static int AddParam(void *in_node, void *param)
{
    *(int *)in_node += *(int *)param;

    return (SUCCESS);
}
static void DuplicateArrays(int *arr1, int *arr2, size_t size)
{
    size_t i = 0;
    
    for(i = 0; i < size; ++i)
    {
        *(arr2 + i) = *(arr1 + i);
    }
}

static int IsArraysSame(int *arr1, int *arr2, size_t size, int param)
{
    size_t i = 0;
    int same = TRUE;
    
    for(i = 0; i < size && same == TRUE; ++i)
    {
        same = *(arr2 + i) == (*(arr1 + i) + param)? TRUE:FALSE;
    }

    return (TRUE);
}

int CompareInts(const void *in_tree, const void *param)
{
    return (*(int *)in_tree - *(int *)param);
}
