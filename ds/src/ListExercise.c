/*
Dev:
Rev:
Status:
Date:
*/
#include <stddef.h> /*NULL*/
#include <assert.h> /*assert*/
#include "ListExercise.h"

enum RESULT
{
	FAIL = -1,
	SUCCESS = 0
};

/*Flips the list, causing the head to be the tail and the other way around*/
node_t *Flip(node_t *head)
{
	node_t *current = NULL;
	node_t *follow = NULL;

	assert(NULL != head);
	
	current = head->next;
	head->next = NULL;
	
	while (NULL != head->next)
	{
		follow = current->next;
		current->next = head;
		head = current;
		current = head->next;
	}

	return (head); 
}

/*Confirms if a list has a loop or not*/
int HasLoop(const node_t *head)
{
	node_t *sheep = NULL;
	node_t *dog = NULL;
	
	assert(NULL != head);
	
	sheep = head;
	dog = head;
	
	while (NULL != dog->next && NULL != sheep && NULL != dog)
	{
		if (sheep == dog)
		{
			return (SUCCESS);
		}
		
		sheep = sheep->next;
		dog = dog->next->next; 
	}
	
	return (FAIL);
}


/*Looks for a node that is the intersection of 2 lists*/
/*node_t *FindIntersection(node_t *head1, node_t *head2)
{
	assert(NULL != head);
	
}*/
