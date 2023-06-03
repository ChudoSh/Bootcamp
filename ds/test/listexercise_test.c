/*
Dev: BarSH
Rev: MariaP
Status: Approved
Date: 3.5.23
*/
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
	return (0);		
}


void TestUnit1()
{
	node_t head = {NULL, NULL};
	node_t node2 = {NULL, NULL};
	node_t node3 = {NULL, NULL};
	node_t node4 = {NULL, NULL};
	node_t node5 = {NULL, NULL};
	node_t node6 = {NULL, NULL};
	node_t tail = {NULL, NULL};
	
	head.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &tail;
	tail.next = NULL;

	Flip(&head);
	
	if(tail.next == &node6)
	{
		printf("Flip successful!\n");
		return;
	}
	
	else	
	{
		printf("Flip failed..\n");
		return;
	}

}

void TestUnit2()
{
	node_t head = {NULL, NULL};
	node_t node2 = {NULL, NULL};
	node_t node3 = {NULL, NULL};
	node_t node4 = {NULL, NULL};
	node_t node5 = {NULL, NULL};
	node_t node6 = {NULL, NULL};
	node_t tail = {NULL, NULL};
	
	
	head.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &node6;
	node6.next = &tail;
	tail.next = &node4;
	
	if(1 == HasLoop(&head))
	{
		printf("Loop detection successful!\n");
		return;
	}
	
	else	
	{
		printf("Loop detection failed..\n");
		return;
	}
}

void TestUnit3()
{
	node_t head1 = {NULL, NULL};
	node_t node2 = {NULL, NULL};
	node_t node3 = {NULL, NULL};
	node_t node4 = {NULL, NULL};
	node_t node5 = {NULL, NULL};
	node_t tail1 = {NULL, NULL};
	
	node_t head2 = {NULL, NULL};
	node_t node8 = {NULL, NULL};
	node_t node9 = {NULL, NULL};
	node_t node10 = {NULL, NULL};
	
	
	head1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = &node5;
	node5.next = &tail1;
	tail1.next = NULL;
	
	head2.next = &node8;
	node8.next = &node9;
	node9.next = &node10;
	node10.next = &node5;
	
	
	if(&node5 == FindIntersection(&head1, &head2))
	{
		printf("Intersection found - successful!\n");
		return;
	}
	
	else	
	{
		printf("Intersection not found..\n");
		return;
	}
	
}



