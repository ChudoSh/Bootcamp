/*
Dev: BarSH
Rev: 
Date: 17.5.23
Status: 
*/

#ifndef __PQUEUE_H__
#define __PQUEUE_H__

#include <stddef.h> /* size_t */

#include "sortlist.h" 

typedef struct PQueue pq_t;


/*****************************************************************************/
/*
Description: Creates a priority queue.
Arguments:
	- compare : A valid pointer to a comparison function.
Return: A pointer to the created queue, NULL if failed.

Time complexity: O(1).
Space complexity: O(1).
*/

pq_t *PQCreate(int (*compare)(const void *,const void *));

/*****************************************************************************/
/*
Description: Destroys a priority queue.
Arguments:
	- compare : A valid pointer to a comparison function.
Return: 
	A pointer to the created queue.

Time complexity: O(1).
Space complexity: O(1).
*/

void PQDestroy(pq_t *pq);

/*****************************************************************************/
/*
Description: Insert an element into the priority queue.
Arguments:
	- pq : A valid pointer to a pqueue.
	- data : A valid pointer to a data. 
Return: 
	0 if succeeded, -1 otherwise.
Time complexity: O(1).
Space complexity: O(1).
*/

int PQEnqueue(pq_t *pq, void *data);

/*****************************************************************************/
/*
Description: Removes an element from the priority queue.
Arguments:
	- pq : A valid pointer to a pqueue.
Return: 
	The value of the removed node.
Time complexity: O(1).
Space complexity: O(1).
*/
void *PQDequeue(pq_t *pq);

/***********************************************************************/
/*
Description: Shows the value of first pqueue element.
Arguments: 
	- pq : A valid pointer to a pqueue.
Return: 
	The value of the highest priority node.
Time complexity: O(1)
Space complexity: O(1)
*/
void *PQPeek(const pq_t *pq);

/*****************************************************************************/
/*
Description: Erases an element from the pqueue by value.
Arguments:
	- pq : A valid pointer to a pqueue.
	- is_match : A valid pointer to a match function, return TRUE or FALSE.
	- param : A valid pointer to a data. 
Return: 
	Return 0 if succeeded, -1 otherwise.
Time complexity: O(n).
Space complexity: O(1).
*/
int PQErase(pq_t *pq, int (*is_match)(const void *, const void *), void *param);

/*****************************************************************************/
/*
Description: Empty the queue.
Arguments:

Return: 

Time complexity: O().
Space complexity: O().
*/

void PQClear(pq_t *pq);
/*****************************************************************************/
/*
Description: Count elements in the queue. 
Arguments:


Time complexity: O().
Space complexity: O().
*/

size_t PQSize(const pq_t *pq);

/*****************************************************************************/
/*
Description: Count elements in the queue. 
Arguments:


Time complexity: O().
Space complexity: O().
*/
int PQIsEmpty(const pq_t *pq);

#endif /* __PQUEUE_H__ */
