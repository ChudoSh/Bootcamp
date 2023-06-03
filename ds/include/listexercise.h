/*
Dev: BarSH
Rev: MariaP
Status: Approved
Date: 3.5.23
*/

#ifndef __SLISTEXERCISE_H__
#define __SLISTEXERCISE_H__

typedef struct node
{
	void *data;
	struct node *next;
}node_t;


/**************************************************************/
/*
Description: Flips the given list.
Arguments: 
	- head : A valid pointer to the head of the list.
Return: 
	Returns the head to the fliped list.
Time complexity: O(1)
Space complexity: O(1)
*/
/*Reverses the order of a given Slist.*/
node_t *Flip(node_t *head);

/**************************************************************/
/*
Description: Check whether or not the list is looped.
Arguments: 
	- head : A valid pointer to the head of the list.
Return: 
	1 if looped, 0 otherwise. 
Time complexity: O(n)
Space complexity: O(1)
*/
/*Tells whether a given slist has loop*/
int HasLoop(const node_t *head);

/**************************************************************/
/*
Description: Check if there is an intersection beteween lists, returns the intersection point if so. 
Arguments:
	- head1: A valid pointer to the head of the list.
	- head2: A valid pointer to the head of the list. 
Return: 
	The intersection point, NULL otherwise.
Time complexity: O(n)
Space complexity: O(1) 
*/
/*Returns a pointer to a first node mutual to both slist, if any */
node_t *FindIntersection(node_t *head1, node_t *head2);


#endif /*__SLISTEXER_H__*/
