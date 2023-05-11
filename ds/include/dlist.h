/*
Dev: BarSH
Rev: Eylon
Status: Approved
Date: 7.5.23
*/

#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */

typedef struct Node node_t;

typedef struct DList dlist_t;

typedef node_t *dlist_iter_t;



/***********************************************************************/
/*
Description: Creates a dooubly linked list. 
Arguments: 
	None.
Return: 
	Return a pointer to a doubly linked list. 
Time complexity: O(1).
Space complexity: O(1).
*/
dlist_t *DListCreate(void);

/***********************************************************************/
/*
Description: Eliminates a doubly linked list.
Arguments:
	- list : A valid pointer to doubly linked list.
Return: 
	None.
Time complexity: O(n).
Space complexity: O(1).
*/
void DListDestroy(dlist_t *list);

/***********************************************************************/
/*
Description: Counts the number of noeds in the list.
Arguments:
	- list : A constant pointer to a doubly linked list.
Return: 
	Returns the number of nodes in the list. 
Time complexity: O(n).
Space complexity: O(1).
*/
size_t DListSize(const dlist_t *list);

/***********************************************************************/
/*
Description: Inserts a new node into the list.
Arguments:
	- where : A valid node pointer in the dlist (iterator).
	- data : A valid pointer to input data.
Return: 
	Return the location of the new node, otherwise returns the tail node.
Time complexity: O(n).
Space complexity: O(1).
*/

dlist_iter_t DListInsert(dlist_iter_t where, void *data);

/***********************************************************************/
/*
Description: Removes a node in the given position. 
Arguments:
	- current : A valid position node pointer. 
Return: 
	The new node of in the current position.
Time complexity: O(1).
Space complexity: O(1).
*/

dlist_iter_t DListRemove(dlist_iter_t current);

/***********************************************************************/
/*
Description: Retrieves the next node.
Arguments:
	- current : A valid node iterator.
Return: 
	Returns the address of the next node current points to. 
Time complexity: O(1).
Space complexity: O(1).
*/

dlist_iter_t DListNext(dlist_iter_t current);

/***********************************************************************/
/*
Description: Retrieves the previous node.
Arguments:
	- current : A valid node iterator.
Return: 
	Returns the address of the previous node current points to. 
Time complexity: O(1).
Space complexity: O(1).
*/
dlist_iter_t DListPrev(dlist_iter_t current);

/***********************************************************************/
/*
Description: Checks whether the list is empty.
Arguments:
	- list : A valid list pointer.
Return: 
	Returns a 1 if the list is empty, 0 otherwise. 
Time complexity: O(1).
Space complexity: O(1).
*/

int DListIsEmpty(const dlist_t *list);

/***********************************************************************/
/*
Description: Finds an value in a list.
Arguments:
	- from : A valid iterator from which to start to look.
	- to : A valid iterator to end the search.
	- match_func : A valid function pointer that compares values, returns 1 if they are equal, else 0.
	- param : A valid pointer to a value to look for.
Return: 
	Returns the node in which the value was found, else returns the 'to' iterator.
Time complexity: O(n).
Space complexity: O(1).
*/

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, int (*match_func)(void *data, const void *param), const void *param) ;

/***********************************************************************/
/*
Description: Operates a function on each node in the list.
Arguments: 
    - from : A valid iter node to start the operation from.
    - to : The last valid iter node to end the operation.
    - action : A valid function pointer that conducts an operation on each node. returns 1 if succceeded, else 0. 
    - action_param : A valid pointer to an additional value. 
Return:
	 1 if successful, 0 if failed. 
Time complexity: O(n).
Space complexity: O(1).
*/

int DListForEach(dlist_iter_t from, dlist_iter_t to, int(*action_func)(void *data, void *param), void *action_param);

/***********************************************************************/
/*
Description: Sets a new value in the node which the iter points to.
Arguments: 
    - position : A valid iter_t node. 
    - data : A value to insert.
Return: 
	None.
Time complexity: O(1).
Space complexity: O(1).
*/

void DListSetData(dlist_iter_t current, void *data);

/***********************************************************************/
/*
Description: Gets the value in the node which the iter points to.
Arguments: 
    - current : A valid iter_t node. 
Return: 
	The value in the node.
Time complexity: O(1).
Space complexity: O(1).
*/

void *DListGetData(dlist_iter_t current);

/***********************************************************************/
/*
Description: Checks whether 2 iter nodes are equal(point to the same location).
Arguments: 
    - iter1 : A valid iter_t node. 
    - iter2 : A valid iter_t node.
Return: 
	1 if equal, else 0.
Time complexity: O(1).
Space complexity: O(1).
*/

int DListIsEqual(dlist_iter_t iter1 , dlist_iter_t iter2);

/***********************************************************************/
/*
Description: Points to the node after head of the list. 
Arguments: 
    - list : A const valid list pointer.
Return: 
	The address after the head nodes.
Time complexity: O(1).
Space complexity: O(1).
*/
dlist_iter_t DListBegin(const dlist_t *list);

/***********************************************************************/
/*
Description: Gets the tail of the list.
Arguments: 
    - list : A const valid list pointer. 
Return: 
	The tail node. 
Time complexity: O(1).
Space complexity: O(1).
*/

dlist_iter_t DListEnd(const dlist_t *list);

/***********************************************************************/
/*
Description: Inserts a new node at the tail of the list.
Arguments: 
    - list : A const valid list pointer. 
    - data : A valid data pointer. 
Return: 
	The node before the tail node if succeeded, else returns the tail node. 
Time complexity: O(1).
Space complexity: O(1).
*/

dlist_iter_t DListPushBack(dlist_t *list, void *data);

/***********************************************************************/
/*
Description: Inserts a new node at the head of the list.
Arguments: 
    - list : A const valid list pointer.
    - data : A valid data pointer. 
Return: 
	The node after the head node if succeeded, else returns the tail node. 
Time complexity: O(1).
Space complexity: O(1).
*/

dlist_iter_t DListPushFront(dlist_t *list, void *data);

/***********************************************************************/
/*
Description: Removes the node at the head of the list.
Arguments: 
    - list : A const valid list pointer.
Return: 
	The node after the head node if succeeded, else returns the tail node. 
Time complexity: O(1).
Space complexity: O(1).
*/

void *DListPopFront(dlist_t *list);

/***********************************************************************/
/*
Description: Removes the node at the tail of the list.
Arguments: 
    - list : A const valid list pointer.
Return: 
	The node before the tail node if succeeded, else returns the tail node. 
Time complexity: O(1).
Space complexity: O(1).
*/

void *DListPopBack(dlist_t *list);

/***********************************************************************/
/*
Description: Appends from one node till another in the source list to a position in the destination list.
Arguments: 
	- dest : A const valid list pointer of the destination.
	- src : A const valid list pointer of the source.
Return: 
	The position in the destination list.
Time complexity: O(1)
Space complexity: O(1)
*/

dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to);

/***********************************************************************/
/*
Description: Looks for mulitple nodes with same value and inserts them into a given output list. 
Arguments: 
    - from: A valid iter node to start the operation from.
    - to : The last valid iter node to end the operation.
    - match_func : A valid function pointer that compares values, returns 1 if they are equal, else 0. 
    - param : A valid pointer to an additional value. 
    - output_list : A valid pointer to the output list. 
Return:
	 Returns 1 if successful, else 0. 
Time complexity: O(n).
Space complexity: O(1).
*/
int DListMultiFind(dlist_iter_t from, dlist_iter_t to, int (*match_func)(void *data, const void *param), const void *param, dlist_t *output_list);

#endif /* __DLIST_H__ */
