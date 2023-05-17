/*
Dev: BarSH
Rev: AnnaB
Date: 8.5.23
Status: Approved
*/

#ifndef __SORT_LIST_H__
#define __SORT_LIST_H__

#include <stddef.h> /* size_t */

#include "dlist.h" 

typedef struct SortList sort_list_t;

typedef struct SortIter
{
	dlist_iter_t iter;
	#ifndef NDEBUG
	sort_list_t *list;
	#endif /*NDEBUG*/
} sort_iter_t;

typedef int (*compare_t)(void *, const void *); /*comparative int*/
typedef int (*action_t)(void *, void *);
typedef compare_t is_match_t; /*reuse name for boolean*/

/***********************************************************************/
/*
Description: Creates a sorted list.
Arguments:
	- compare_t : A calid function pointer to a compare function. 
Return: 
	A pointer to a sorted list, NULL if not.
Time complexity: O(1).
Space complexity: O(1).
*/

sort_list_t *SortListCreate(compare_t);

/***********************************************************************/
/*
Description: Destroys a sorted list.
Arguments:
	- list : A valid sorted list pointer.
Return: 
	Nothing.
Time complexity: O(1).
Space complexity: O(1).
*/

void SortListDestroy(sort_list_t *list);

/***********************************************************************/
/*
Description: Inserts a node into a sorted list. 
Arguments:
	- list : A valid sorted list pointer.
	- data : A valid data pointer
Return: 
	Returns a pointer to node where it was inserted, 
	returns the end of the list if failed. 
Time complexity: O(n).
Space complexity: O(1).
*/

sort_iter_t SortListInsert(sort_list_t *list, void *data);

/***********************************************************************/
/*
Description: Remove a node from a sorted list. 
Arguments:
	- list : A valid sorted list pointer.
Return: 
	Returns an iterator to node where it was removed. 
Time complexity: O(1).
Space complexity: O(1).
*/
sort_iter_t SortListRemove(sort_iter_t current);

/***********************************************************************/
/*
Description: Finds a node in the list with the same given value.
Arguments:
	- from : A sorted list iteratro to start the search from.
	- to : A sorted list iteratro to start the search from.
	- list : A valid sorted list pointer.
	- param : A data pointer.
Return: 
	Returns a an iterator to the node where the value was found,
	returns the end of the lists if failed. 
Time complexity: O(1).
Space complexity: O(1).
*/
sort_iter_t SortListFind(sort_iter_t from, sort_iter_t to, 
						 sort_list_t *list, void *param);

/***********************************************************************/
/* 
Description: should not change list data, un-sorting list by 
			 changing data is undefined.
Arguments:
	- from : A sort list iterator to start the operations from. 
	- to : A sort list iterator that where the operations should end.
	- action : A valid pointer to an action function.
	- action_param : A valid parameter to conduct the operations with.
Return: 
Time complexity: O(n).
Space complexity: O(1).
*/

int SortListForEach(sort_iter_t from, sort_iter_t to, 
					action_t action, void *action_param);

/***********************************************************************/
/*
Description: Gets the # of nodes in a sorted list. 
Arguments:
	- list : A valid pointer to a sorted list.
Return: 
	The size of the list. 
Time complexity: O(n).
Space complexity: O(1).
*/

size_t SortListSize(const sort_list_t *list);

/***********************************************************************/
/*
Description: Checks whether the list is empty or not. 
Arguments:
	- list : A valid sorted list pointer.
Return: 
	1 if empty, 0 otherwise.
Time complexity: O(1).
Space complexity: O(1).
*/

int SortListIsEmpty(sort_list_t *list);

/***********************************************************************/
/*
Description: Gets iterator's the next node.
Arguments:
	- current : A sorted list iterator.
Return: 
	The next node the iterator points to.
Time complexity: O(1).
Space complexity: O(1).
*/

sort_iter_t SortListNext(sort_iter_t current);

/***********************************************************************/
/*
Description: Gets iterator's the previous node.
Arguments:
	- current : A sorted list iterator.
Return: 
	The previous node the iterator points to.
Time complexity: O(1).
Space complexity: O(1).
*/
sort_iter_t SortListPrev(sort_iter_t current);

/***********************************************************************/
/*
Description: Gets the next node of head node.
Arguments:
	- current : A valid pointer to a sorted list.
Return: 
	An itertor that points to the node next to the head.
Time complexity: O(1).
Space complexity: O(1).
*/
sort_iter_t SortListBegin(const sort_list_t *list);

/***********************************************************************/
/*
Description: Gets the tail node.
Arguments:
	- current : A valid pointer to a sorted list.
Return: 
	An itertor that points to the tail node.
Time complexity: O(1).
Space complexity: O(1).
*/
sort_iter_t SortListEnd(const sort_list_t *list);

/***********************************************************************/
/*
Description: Gets the data of the current iterator.
Arguments:
	- current : A sorted list iterator.
Return: 
	A pointer to the data the node holds.
Time complexity: O(1).
Space complexity: O(1).
*/
void *SortListGetData(sort_iter_t current);

/***********************************************************************/
/*
Description: Removes the next node of head node.
Arguments:
	- current : A sorted list iterator.
Return: 
	A pointer to the data the node held.
Time complexity: O(1).
Space complexity: O(1).
*/
void *SortListPopFront(sort_list_t *list);

/***********************************************************************/
/*
Description: Removes the previous node to the tail node.
Arguments:
	- current : A sorted list iterator.
Return: 
	A pointer to the data the node held.
Time complexity: O(1).
Space complexity: O(1).
*/
void *SortListPopBack(sort_list_t *list);

/***********************************************************************/
/*
Description: Checks whether two iterators are equal.
Arguments:
	- iter1 : A sorted list iterator. 
	- iter2 : A sorted list iterator.
Return: 
	1 if they are equal, 0 otherwise.
Time complexity: O(1).
Space complexity: O(1).
*/
int SortListIsEqual(sort_iter_t iter1 , sort_iter_t iter2);

/***********************************************************************/
/*
Description: Merges to lists into one, the compare functions of the lists
			 must be equal.
Arguments:
	- dest : A valid pointer to a  destination sorted list.
	- src : A valid pointer to a  source sorted list.
Return: Iterator to the "from" node in its new location.
Time complexity: O(n).
Space complexity: O(1).
*/

void SortListMerge(sort_list_t *dest, sort_list_t *src);

/***********************************************************************/
/*
Description: Checks whether a node in the list with the same given value.
Arguments:
	- from : A sorted list iteratro to start the search from.
	- to : A sorted list iteratro to start the search from.
	- is_match : A valid boolean function pointer.
	- param : A data pointer.
Return: 
	Returns a an iterator to the node where the value was found,
	returns the end of the lists if failed. 
Time complexity: O(1).
Space complexity: O(1).
*/
sort_iter_t SortListFindIf(sort_iter_t from, sort_iter_t to, 
						   is_match_t is_match, void *param);

#endif /* __SORT_LIST_H__ */
