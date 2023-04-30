/*
Dev: BarSH
Rev: 
Date: 
Status: 
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

typedef int(*is_match_t)(const void *, void *);

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
Description: Inserts a new node into the list
Arguments: 
    - from : A valid iterator that points to the starting node needed to match.
    - to :  A valid iterator that points to the end node.
    - value : A pointer to a value to compare the nodes with.
    - matcher : A pointer to a function that is meant to match between the values.
Return: 
Time complexity: O(n).
Space complexity: O(1).
*/
iter_t SListFind(iter_t from, iter_t to, const void *value, is_match_t matcher) ;

/***********************************************************************/
/*
Description: Insert a new node to the list.
Arguments: 
    - where : An itertor to the position which the new nodes will be inserted.
    - value : A valid pointer to a value.
Return: 
	The iterator to the location of the new node.
Time complexity: O(1).
Space complexity: O(1).
*/
iter_t SListInsert(iter_t where, void *value);

/***********************************************************************/
/*

Description: 
Arguments: 
    - 
    - 
Return: 
Time complexity: O().
Space complexity: O().
*/
iter_t SListRemove(iter_t where);

/***********************************************************************/
/*

Description: 
Arguments: 
    - 
    - 
Return: 
Time complexity: O().
Space complexity: O().
*/
size_t SListCount(const slist_t *list);

/***********************************************************************/
/*

Description: 
Arguments: 
    - 
    - 
Return: 
Time complexity: O().
Space complexity: O().
*/
iter_t SListEnd(const slist_t *list);

/***********************************************************************/
/*

Description: Indicates the head of the list. 
Arguments: 
    - list : A const valid list pointer.
Return: 
	An iterator to the head of the list.
Time complexity: O(1).
Space complexity: O(n).
*/
iter_t SListBegin(const slist_t *list);

/***********************************************************************/
/*

Description: 
Arguments: 
    - 
    - 
Return: 
Time complexity: O().
Space complexity: O().
*/
void SListForEach(iter_t from, iter_t to, action_t action, void *param);

/***********************************************************************/
/*

Description: 
Arguments: 
    - 
    - 
Return: 
Time complexity: O().
Space complexity: O().
*/
void SListSet(iter_t position, void *value);

/***********************************************************************/
/*

Description: 
Arguments: 
    - 
    - 
Return: 
Time complexity: O().
Space complexity: O().
*/
void *SListGet(iter_t position);

/***********************************************************************/
/*

Description: 
Arguments: 
    - 
    - 
Return: 
Time complexity: O().
Space complexity: O().
*/
iter_t SListNext(iter_t position);

/***********************************************************************/
/*

Description: 
Arguments: 
    - 
    - 
Return: 
Time complexity: O().
Space complexity: O().
*/
int SListIterIsEqual(iter_t iter1 , iter_t iter2);


#endif /*__SLIST__*/
