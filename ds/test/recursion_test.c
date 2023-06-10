

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include "stack.h"
#include "recursion.h"

static void Test(int val, const char *func, int line);
static void TestFib();
static void TestFlip();
static void TestSortStack();
static void RecStrlen();
static void RecStrcmp();
static void RecStrcpy();
static void RecStrcat();

int main()
{
	TestFib();
	TestFlip();
	TestSortStack();
	RecStrlen();
	RecStrcmp();
	RecStrcpy();
	RecStrcat();
	
   	return (0); 
}

static void TestFib()
{
    Test(13 == Fibonnachi(7), "Fibonnachi", __LINE__);
}

static void TestFlip()
{
	node_t head = {"1", NULL};
	node_t node2 = {"2", NULL};
	node_t node3 = {"3", NULL};
	node_t node4 = {"4", NULL};
	node_t node5 = {"5", NULL};
	node_t node6 = {"6", NULL};
	node_t tail = {"7", NULL};
	
	head.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &tail;
	tail.next = NULL;

	Flip(&head);
	
	Test(&node6 == tail.next, "RecursiveFlip", __LINE__);
}

static void TestSortStack()
{
    stack_t *stack = StackCreate(5, sizeof(int));
    int i = 0;
    int x[5] = {10,1,7,2,3}; 

    for (i = 0; i < 5; ++i)
    {
        StackPush(stack, &x[i]);
    }
	
    stack  = SortStack(stack, 5);

    for (i = 0; i < 5; ++i)
    {
        x[i] = *(int *)StackPeek(stack);
        StackPop(stack);
		if (x[i] > *(int*)StackPeek(stack))
		{
			printf("stack sort failed..");
		}
    }

	StackDestroy(stack);

    printf("Stack Sort Sucess!\n");
    
}

static void RecStrlen()
{
	char *str = "shalom";
	size_t x = Strlen(str);

	Test(6 == x, "RecStrlen", __LINE__);
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

static void RecStrcmp()
{
	Test(0 < Strcmp("shalom", "goodbye"), "RecStrcmp", __LINE__);
}


static void RecStrcpy()
{
	char dest[7] = {'\0'};

	Strcpy(dest, "shalom");

	Test(0 == Strcmp(dest, "shalom"), "Strcpy", __LINE__);
}

static void RecStrcat()
{
	char dest[15] = {'b','o','k','e','r','t','o','v'};

	Strcat(dest, "shalom");

	Test(0 == Strcmp(dest, "bokertovshalom"), "Strcat", __LINE__);
}