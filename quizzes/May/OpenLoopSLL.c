#include <stddef.h> /*NULL*/
#include <assert.h> /*assert*/
#include <stdio.h>


typedef struct node
{
	void *data;
	struct node *next;
}node_t;


int IsSListLooped(node_t *head);
void UnLoop(node_t *looped, node_t *head);

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
	tail.next = &node4;
	
	if(1 == IsSListLooped(&head) && NULL == tail.next)
	{
		printf("Loop detection and removal successful!\n");
	}
	
	else	
	{
		printf("Loop detection failed..\n");
	}
	
	return (0);
}

int IsSListLooped(node_t *head)
{
	node_t *fast_iter = NULL;
	node_t *slow_iter = NULL;
	
	assert(NULL != head);
	
	fast_iter = head;
	slow_iter = head;
	
	while (NULL != fast_iter->next && NULL != fast_iter)
	{
		slow_iter = slow_iter->next;
		fast_iter = fast_iter->next->next;
		 
		if (fast_iter == slow_iter)
		{
			UnLoop(fast_iter, head);
			return (1);
		} 
	}
	
	return (0);
}

void UnLoop(node_t *looped, node_t *head)
{
	node_t *iter1 = NULL;
	node_t *iter2 = NULL;
	size_t k = 1;
	size_t i = 0;
	
	assert(NULL != head);
	assert(NULL != looped);
	
	iter1 = looped; 
	iter2 = looped;
	
    while (iter1->next != iter2) 
    {
        iter1 = iter1->next;
        ++(k);
    }
 
    /*Fix one pointer to head*/
    iter1 = head;
  	/*And the other pointer to k nodes after head*/
    iter2 = head;
   
    for (i = 0; i < k; ++i)
    {
        iter2 = iter2->next;
    }
 
    /*Move both pointers at the same pace,
      they will meet at loop starting node */
    while (iter2 != iter1)
    {
        iter1 = iter1->next;
        iter2 = iter2->next;
    }
 
    /*Set the next node of the loop ending node
      to fix the loop */
    iter2->next = NULL;
}

