/*
Developer:BarSH
Reviewer:MariaP
status: Approved
date: 18/06/23
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "avl.h" 

static void TestCreatenDestroy();
static void TestInsertSizeForEach();
static void TestRemove();
static void TestBalance();
static int Compare(const void *a, const void *b);
static void AutomatedTest(int val, const char *func, int line);

int main()
{
    TestCreatenDestroy();
    TestInsertSizeForEach();
    TestRemove();
    TestBalance();

    return (0);
}

static void TestCreatenDestroy()
{
    avl_tree_t *tree = AVLCreate(Compare);

    AutomatedTest(AVLIsEmpty(tree), "Create & IsEmpty", __LINE__);
    
    AVLDestroy(tree);
}

static void TestInsertSizeForEach()
{
    int array[20] = {100,45,8,6,7888,13216,156,77,99,333,44,2,0,11,5,66,9,4,7,3};
    size_t i = 0;

    avl_tree_t *tree = AVLCreate(Compare);

    for(i = 0; i < 20; ++i)
    { 
        AVLInsert(tree, &array[i]);
    } 

    PrintTree(tree);

    AutomatedTest(20 == AVLCount(tree), "Insert & Size", __LINE__);

    AVLDestroy(tree);

}

static void TestRemove()
{
    int array[20] = {100,45,8,6,7888,13216,156,77,99,333,44,2,0,11,5,66,9,4,7,3};
    size_t i = 0;

    avl_tree_t *tree = AVLCreate(Compare);

    for(i = 0; i < 20; ++i)
    { 
        AVLInsert(tree, &array[i]);
    }

    AVLRemove(tree, &array[1]);
    AVLRemove(tree, &array[18]); 

    AutomatedTest(18 == AVLCount(tree), "Find & Remove",__LINE__);

    AVLDestroy(tree);
}

static void TestBalance()
{
    int a = 10;
    int b = 7; 
    int c = 5;

    avl_tree_t *tree = AVLCreate(Compare);

    
    AVLInsert(tree, &a);
    AVLInsert(tree, &b);
    AVLInsert(tree, &c);

    AutomatedTest(7 == *(int *)GetData(GetRoot(tree)),"Blance", __LINE__);

    AVLDestroy(tree);
}


static int Compare(const void *a, const void *b)
{   
    return (*(int *)a - *(int *)b);
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




