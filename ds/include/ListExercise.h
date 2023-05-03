/*
Dev: BarSH
Rev: MariaP
Status: Approved
Date: 3.5.23
*/

#ifndef __SLISTEXER_H__
#define __SLISTEXER_H__

typedef struct node
{

	void *data;
	struct node *next;


}node_t;


/**************************************************************/
/*
Description: 
Arguments: 
Return: 
Time complexity: 
Space complexity: 
*/
/*Reverses the order of a given Slist.*/
node_t *Flip(node_t *head);

/**************************************************************/
/*
Description: 
Arguments: 
Return: 
Time complexity: 
Space complexity: 
*/
/*Tells whether a given slist has loop*/
int HasLoop(const node_t *head);

/**************************************************************/
/*
Description: 
Arguments: 
Return: 
Time complexity: 
Space complexity: 
*/
/*Returns a pointer to a first node mutual to both slist, if any */
node_t *FindIntersection(node_t *head1, node_t *head2);


#endif /*__SLISTEXER_H__*/
