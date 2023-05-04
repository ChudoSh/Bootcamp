#ifndef __DLIST_H__
#define __DLIST_H__

#include <stddef.h> /* size_t */

typedef struct Node node_t;
/*
{
	void *data;
	node_t *next;
	node_t *previous;
}
*/

typedef struct DList dlist_t;
/*
{
	node_t head;
	node_t tail;
};
*/

typedef node_t *dlist_iter_t;



/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_t *DListCreate(void);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void DListDestroy(dlist_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

size_t DListSize(const dlist_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListInsert(dlist_iter_t where, void *data);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListRemove(dlist_iter_t current);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListNext(dlist_iter_t current);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListPrev(dlist_iter_t current);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

int DListIsEmpty(const dlist_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, int (*match_func)(void *data, const void *param), const void *param) ;

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

int DListForEach(dlist_iter_t from, dlist_iter_t to, int(*action_func)(void *data, void *param), void *action_param);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void DListSetData(dlist_iter_t current, void *data);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void *DListGetData(dlist_iter_t current);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

int DListIsEqual(dlist_iter_t iter1 , dlist_iter_t iter2);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListBegin(const dlist_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListEnd(const dlist_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListPushBack(dlist_t *list, void *data);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListPushFront(dlist_t *list, void *data);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void *DListPopFront(dlist_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/

void *DListPopBack(dlist_t *list);

/***********************************************************************/
/*
Description: 
Arguments:
Return: Iterator to the "from" node in its new location.

Time complexity: O().
Space complexity: O().
*/

dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to);

/***********************************************************************/
/*
Description: 
Arguments:
Return: 

Time complexity: O().
Space complexity: O().
*/


int DListMultiFind(dlist_iter_t from, dlist_iter_t to, int (*match_func)(void *data, const void *param), const void *param, dlist_t *output_list);

#endif /* __DLIST_H__ */
