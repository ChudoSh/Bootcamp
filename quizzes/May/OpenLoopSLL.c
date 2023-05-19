#include <stddef.h> /*NULL*/
#include <assert.h> /*assert*/

#include "ListExercise.h"

typedef struct node
{
	void *data;
	struct node *next;
}node_t;


int IsSListLooped(const node_t *head);
node_t UnLoop(node_t *head);

int main()
{
	

}

node_t * IsSListLooped(const node_t *head)
{
	const node_t *fast_iter = NULL;
	const node_t *slow_iter = NULL;
	
	assert(NULL != head);
	
	fast_iter = head;
	slow_iter = head;
	
	while (NULL != fast_iter->next && NULL != fast_iter)
	{
		slow_iter = slow_iter->next;
		fast_iter = fast_iter->next->next;
		 
		if (fast_iter == slow_iter)
		{
			break;
		} 
	}
	
	fast_iter = head;
	
	while (slow_iter == fast_iter)
	{
		slow_iter = slow_iter->next;
		fast_iter = fast_iter->next;
	}
	
	slow_iter->next = NULL;
	s
	return (head);
}

node_t *UnLoop(const node_t *head)
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
			return (TRUE);
		} 
	}
	
	return (head);
}

