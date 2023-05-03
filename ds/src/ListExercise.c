/*
Dev: BarSH
Rev: MariaP
Status: Approved
Date: 3.5.23
*/

#include <stddef.h> /*NULL*/
#include <assert.h> /*assert*/

#include "ListExercise.h"

enum RESULT
{
	FAIL = 0,
	SUCCESS = 1
};

/*Flips the list, causing the head to be the tail and the other way around*/
node_t *Flip(node_t *head)
{	
	node_t *current = NULL;
	node_t *follow = NULL;

	assert(NULL != head);
	
	current = head->next;
	head->next = NULL;
	
	while (NULL != current)
	{
		follow = current->next;
		current->next = head;
		head = current;
		current = follow;
	}
	
	return (head); 
}

/*Confirms if a list has a loop or not*/
int HasLoop(const node_t *head)
{
	const node_t *sheep = NULL;
	const node_t *wolf = NULL;
	
	assert(NULL != head);
	
	sheep = head;
	wolf = head;
	
	while (NULL != wolf->next && NULL != wolf)
	{
		sheep = sheep->next;
		wolf = wolf->next->next;
		 
		if (sheep == wolf)
		{
			return (SUCCESS);
		} 
	}
	
	return (FAIL);
}


/*Looks for a node that is the intersection of 2 lists*/
node_t *FindIntersection(node_t *head1, node_t *head2)
{
	node_t *iter1 = NULL;
	node_t *iter2 = NULL;
	
	size_t count1 = 0;
	size_t count2 = 0; 
	
	assert(NULL != head1);
	assert(NULL != head2);
	
	iter1 = head1;
	iter2 = head2;
	
	while (NULL != iter1->next)
	{
		iter1 = iter1->next;
		++(count1);
	}
	
	while (NULL != iter2->next)
	{
		iter2 = iter2->next;
		++(count2);
	}
	
	if (iter1->next != iter2->next)
	{
		return (NULL);
	}
	
	iter1 = head1;
	iter2 = head2;
	
	while (iter1 != iter2)
	{
		if (count1 > count2)
		{
			--(count1);
			iter1 = iter1->next;
		}
		
		else if(count1 < count2)
		{
			--(count2);
			iter2 = iter2->next;
		}
		
		else
		{
			iter1 = iter1->next; 
			iter2 = iter2->next;
		}
	}
	
	return (iter1);		
}

