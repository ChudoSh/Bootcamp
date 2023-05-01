



#include "ListExercise.h"




node_t *Flip(node_t *head)
{
	node_t *temp1 = NULL;
	node_t *temp2 = NULL;
	node_t *temp3 = NULL;

	assert(NULL != head);
	
	temp1 = head->next;
	temp2 = head->next->next;
	temp3 = head->next->next->next;
	temp1->next = head;
	
	while (NULL != temp3)
	{
		temp2->next = temp1;
		temp1 = temp3; 
		temp3->next = temp2; 
		temp2 = temp1->next; 
		temp3 = temp1->next-next;	
	}
	
	head->next = NULL;
	temp2->next = temp1;
	
	return (temp2);
}



int HasLoop(const node_t *head)
{
	size_t
}
