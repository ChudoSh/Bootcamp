/*
Dev: BarSH
Rev: YaronM
Date: 2.5.23
Status: Approved
*/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t, NULL */
#include "slist.h" /*slist_t*/

typedef slist_t queue_t;

/*void SListAppend(slist_t *dest, slist_t *src);*/

/***********************************************************************/
/*
Description: Creates a queue.
Arguments: 
	- None.
Return:
	Return a pointer to a queue_t if succeeded, null otherwise. 
Time complexity: O(1)
Space complexity: O(1)
*/
queue_t *QCreate(void);

/***********************************************************************/
/*
Description: Destroys a queue. 
Arguments: 
	- queue : A valid queue pointer. 
Return: 
	Nothing.	
Time complexity: O(n) 
Space complexity: O(1)
*/
void QDestroy(queue_t *queue);


/***********************************************************************/
/*
Description: Add's a new element to the queue.
Arguments: 
	- queue : A valid queue pointer. 
	- value : A valid const poiner to a value.	
Return: 
	Returns 0 if succeeded, -1 otherwise.
Time complexity: O(1)
Space complexity: O(1)
*/
int QEnqueue(queue_t *queue, const void *value);

/***********************************************************************/
/*
Description: Remove's an element from the queue.
Arguments: 
	- queue : A valid queue pointer.
Return: 
	Nothing.
Time complexity: O(1)
Space complexity: O(1)
*/
void QDequeue(queue_t *queue);

/***********************************************************************/
/*
Description: Indicates whether the queue is empty or not. 
Arguments: 
	- queue : A const valid queue pointer.
Return: 
	Returns 1 if empty, 0 otherwise. 
Time complexity: O(1)
Space complexity: O(1)
*/
int QIsEmpty(const queue_t *queue);


/***********************************************************************/
/*
Description: Reveales the front element. 
Arguments: 
	- queue : A const valid queue pointer.
Return: 
	Retruns the value of the first element. 
Time complexity: O(1)
Space complexity: O(1)
*/
void *QPeek(const queue_t *queue);

/***********************************************************************/
/*
Description: Shows how many elements are in the queue.
Arguments: 
	- queue : A const valid queue pointer.
Return: 
	Returns the number of elements in the queue.
Time complexity: O(n)
Space complexity: O(1)
*/
size_t QSize(const queue_t *queue);

/***********************************************************************/
/*
Description: Appends a source queue to a destination queue, empties the source.
Arguments: 
	- dest : A const valid queue pointer of the destination.
	- src : A const valid queue pointer of the source.
Return: 
	Nothing.
Time complexity: O(1)
Space complexity: O(1)
*/
void QAppend(queue_t *dest, queue_t *src);

#endif /*__QUEUE_H__*/
