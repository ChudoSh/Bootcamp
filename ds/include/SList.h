/*
Dev: BarSH
Rev: Oleg
Date: 1.5.23
Status: Approved
*/ 
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h> /* size_t, NULL */

/*
Node
{
	void *value;
	node_t *next;
}
*/
typedef struct Node node_t;

/*
SList
{
	node_t *head;
	node_t *tail;
};
*/
typedef struct SList slist_t;

typedef node_t *iter_t;

typedef int (*is_match_t)(const void *, void *);

typedef void *(*action_t)(void *, void *);

/***********************************************************************/
/*
Description: Creates a list.
Arguments: 
	None.
Return: 
	Returns a pointer to a list of type slist_t.
Time complexity: O(1).
Space complexity: O(1).
*/
slist_t *SListCreate(void);

/***********************************************************************/
/*
Description: Destroys a list. 
Arguments: 
    - list : A valid list pointer;
Return: 
	None. 
Time complexity: O(n).
Space complexity: O(n).
*/
void SListDestroy(slist_t *list);

/***********************************************************************/
/*
Description: Finds a node into the list
Arguments: 
    - from : A valid iterator that points to the starting node needed to match.
    - to :  A valid iterator that points to the end node.
    - value : A const valid pointer to a value to compare the nodes with.
    - matcher : A valid pointer to a function that is meant to match between the designated type of values.
Return: 
	If the value is found it return the iterator to the value, else returns 'to'.
Time complexity: O(n).
Space complexity: O(1).
*/
iter_t SListFind(iter_t from, iter_t to, const void *value, is_match_t matcher);

/***********************************************************************/
/*
Description: Insert a new node to the list.
Arguments: 
    - where : A valid itertor to a position which the new node will be inserted.
    - value : A valid pointer to a value.
Return: 
	The iterator to the location of the new node.
Time complexity: O(1).
Space complexity: O(1).
*/
iter_t SListInsert(iter_t where, void *value);

/***********************************************************************/
/*
Description: Remove a node from the list
Arguments: 
    - where : A valid iterator to a position which node will be removed.
Return: 
	Returns the next node.
Time complexity: O(1).
Space complexity: O(1).
*/
iter_t SListRemove(iter_t where);

/***********************************************************************/
/*
Description: Counts the number of nodes
Arguments: 
    - list : A const valid list pointer.
Return: 
	A size_t number of nodes.
Time complexity: O(1).
Space complexity: O(1).
*/
size_t SListCount(const slist_t *list);

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
iter_t SListEnd(const slist_t *list);

/***********************************************************************/
/*
Description: Indicates the head of the list. 
Arguments: 
    - list : A const valid list pointer.
Return: 
	The head node.
Time complexity: O(1).
Space complexity: O(1).
*/
iter_t SListBegin(const slist_t *list);

/***********************************************************************/
/*
Description: Operates a function to each node in the list.
Arguments: 
    - to : A valid iter node to start the operation from.
    - from : The last valid iter node to end the operation.
    - action : A valid function pointer that conducts an operation on each node. 
    - param : A valid pointer to an additional value. 
Return:
	 Nothing. 
Time complexity: O(n).
Space complexity: O(1).
*/
void SListForEach(iter_t from, iter_t to, action_t action, void *param);

/***********************************************************************/
/*
Description: Sets a new value in the node which the iter points to.
Arguments: 
    - position : A valid iter_t node. 
    - value : A value to insert.
Return: 
	None.
Time complexity: O(1).
Space complexity: O(1).
*/
void SListSet(iter_t position, void *value);

/***********************************************************************/
/*
Description: Gets the value in the node which the iter points to.
Arguments: 
    - position : A valid iter_t node. 
Return: 
	The value in the node.
Time complexity: O(1).
Space complexity: O(1).
*/
void *SListGet(iter_t position);

/***********************************************************************/
/*
Description: Gets the next value in the node which the iter points to.
Arguments: 
    - position : A valid iter_t node. 
Return: 
	The next node.
Time complexity: O(1).
Space complexity: O(1).
*/
iter_t SListNext(iter_t position);

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
int SListIterIsEqual(iter_t iter1 , iter_t iter2);


/***********************************************************************/
/*
Description: Appends a source list to a destination list, empties the source.
Arguments: 
	- dest : A const valid list pointer of the destination.
	- src : A const valid list pointer of the source.
Return: 
	Nothing.
Time complexity: O(1)
Space complexity: O(1)
*/
void SListAppend(slist_t *dest, slist_t *src);


#endif /*__SLIST__*/
