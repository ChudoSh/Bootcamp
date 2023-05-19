#include <stdio.h>
#include <assert.h>


typedef struct node
{
	void *data;
	struct node *next;	
}node_t;

node_t *FindTheNthElementFromTheEndOfList(node_t *head, size_t index)
{
		node_t *end_tip = NULL; 
		node_t *start_tip = NULL;
		
		assert(NULL != head);
		
		start_tip = head;
		end_tip = head; 
		
		while (0 < index)
		{
			end_tip = end_tip->next;
			--(index); 
		}
		
		while (NULL != end_tip->next)
		{
			start_tip = start_tip->next;
			end_tip = end_tip->next; 
		}
		
		return (start_tip);			
}

int main()
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
	
	 
	if (&node3 == FindTheNthElementFromTheEndOfList(&head, 4))
	{
		printf("Test success!\n");
	}
	 
	else
	{
		printf("Test fail..\n");
	}
	return (0);
	
}
