


#include <stdio.h> /*printf*/

#include "ListExercise.h"

void TestUnit2();
void TestUnit1();
void TestUnit3();

enum Status
{
	FAILED,
	SUCCESS
};

int main()
{
	
	TestUnit1();
	TestUnit2();
	TestUnit3();
	return 1;		
}


void TestUnit1()
{
	node_t node1 = {NULL, NULL};
	node_t node2 = {NULL, NULL};
	node_t node3 = {NULL, NULL};
	node_t node4 = {NULL, NULL};
	node_t node5 = {NULL, NULL};
	node_t node6 = {NULL, NULL};
	node_t node7 = {NULL, NULL};
	
	node1.next = NULL;
	node2.next = &node1;
	node3.next = &node2;
	node4.next = &node3;
	node5.next = &node4;
	node6.next = &node5;
	node7.next = &node6;

	
	if(&node1 != Flip(&node7))
	{
		printf("Flip 1 FAILED\n");
		return;
	}
	
	if(&node7 != Flip(&node7))
	{
		printf("Flip 2 FAILED\n");
		return;
	}
	
	printf("Unit 1 Success\n");

}

void TestUnit2()
{
	node_t node1 = {NULL, NULL};
	node_t node2 = {NULL, NULL};
	node_t node3 = {NULL, NULL};
	node_t node4 = {NULL, NULL};
	node_t node5 = {NULL, NULL};
	node_t node6 = {NULL, NULL};
	node_t node7 = {NULL, NULL};
	
	
	node1.next = &node3;
	node2.next = &node1;
	node3.next = &node2;
	node4.next = &node3;
	node5.next = &node4;
	node6.next = &node5;
	node7.next = &node6;
	
	if(SUCCESS != HasLoop(&node7))
	{
		printf("Loop 1 FAILED\n");
		return;
	}
	
	node1.next = &node2;
	
	if(SUCCESS != HasLoop(&node7))
	{
		printf("Loop 2 FAILED\n");
		return;
	}
	
	node1.next = NULL;
	
	if(FAILED != HasLoop(&node7))
	{
		printf("Loop 3 FAILED\n");
		return;
	}
	
	printf("Unit 2 Success\n");
}

void TestUnit3()
{
	node_t node1 = {NULL, NULL};
	node_t node2 = {NULL, NULL};
	node_t node3 = {NULL, NULL};
	node_t node4 = {NULL, NULL};
	node_t node5 = {NULL, NULL};
	node_t node6 = {NULL, NULL};
	node_t node7 = {NULL, NULL};
	
	node_t node8 = {NULL, NULL};
	node_t node9 = {NULL, NULL};
	node_t node10 = {NULL, NULL};
	node_t node11 = {NULL, NULL};
	
	node1.next = NULL;
	node2.next = &node1;
	node3.next = &node2;
	node4.next = &node3;
	node5.next = &node4;
	
	node6.next = &node5;
	node7.next = &node6;
	
	node8.next = &node5;
	node9.next = &node8;
	node10.next = &node9;
	node11.next = &node10;
	
	if(&node5 != FindIntersection(&node11, &node7))
	{
		printf("FindInter 1 FAILED\n");
		return;
	}
	
	node8.next = NULL;
	
	if(NULL != FindIntersection(&node11, &node7))
	{
		printf("FindInter 2 FAILED\n");
		return;
	}
	
	printf("Unit 3 Success \n");
}



