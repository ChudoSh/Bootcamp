#ifndef __SORT_LIST_H__
#define __SORT_LIST_H__

#include <stddef.h> /* size_t */

#include "dlist.h" 

typedef struct SortList sort_list_t;
/*
{
	dlist_t *list;
	compare_t compare;
};
*/

typedef struct SortIter
{
	dlist_iter_t iter;
	#ifndef NDEBUG
	sort_list_t *list;
	#endif /*NDEBUG*/
} sort_iter_t;

typedef int (*compare_t)(void *, void *); /*comparative int*/
typedef int (*action_t)(void *, void *);
typedef compare_t is_match_t; /*reuse name for boolean*/

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

sort_list_t *SortListCreate(compare_t);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void SortListDestroy(sort_list_t *list);

/***********************************************************************/
/*
Description: Creates a sorted list. 
Arguments:
	- compare : A valid function pointer that compares between values.
Return: 
	Returns a pointer to a sorted list, NULL if failed. 
Time complexity: O(n).
Space complexity: O().
*/

sort_iter_t SortListInsert(sort_list_t *list, void *data);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

sort_iter_t SortListRemove(sort_iter_t current);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

sort_iter_t SortListFind(sort_iter_t from, sort_iter_t to, sort_list_t *list, void *param);

/***********************************************************************/
/*
Description: should not change list data, un-sorting list by changing data is undefined 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

int SortListForEach(sort_iter_t from, sort_iter_t to, action_t action, void *action_param);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

size_t SortListSize(const sort_list_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

int SortListIsEmpty(sort_list_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

sort_iter_t SortListNext(sort_iter_t current);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

sort_iter_t SortListPrev(sort_iter_t current);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

sort_iter_t SortListBegin(const sort_list_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

sort_iter_t SortListEnd(const sort_list_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void *SortListGetData(sort_iter_t current);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void *SortListPopFront(sort_list_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void *SortListPopBack(sort_list_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: Iterator to the "from" node in its new location.

Time complexity: O().
Space complexity: O().
*/

void SortListMerge(sort_list_t *dest, sort_list_t *src);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

sort_iter_t SortListFindIf(sort_iter_t from, sort_iter_t to, is_match_t is_match, void *param);

#endif /* __SORT_LIST_H__ */
