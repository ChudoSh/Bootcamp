/*
Dev: BarSH
Rev: YaronM
Date: 2.5.23
Status: Approved
*/

#include <assert.h> /*assert*/

#include "queue.h"

#define IS_EMPTY (0)

/*Creates the queue*/
queue_t *QCreate(void)
{
	return (SListCreate());		
}

/*Destroy's the queue*/
void QDestroy(queue_t *queue)
{	
	assert(NULL != queue);

	SListDestroy(queue);
}

/*Inserts a new node*/
int QEnqueue(queue_t *queue, const void *value)
{
	assert(NULL != queue);
	assert(NULL != value);

	return ((NULL == SListInsert(SListEnd(queue), (void *)value)));	 
}

/*Removes the first element in the queue*/
void QDequeue(queue_t *queue)
{
	assert(NULL != queue);
	
	SListRemove(SListBegin(queue)); 
}

/*Checks if the the queue is empty*/
int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
		
	return (SListBegin(queue) == SListEnd(queue));
}

/*Return the amount of elements in the queue*/
size_t QSize(const queue_t *queue)
{
	assert(NULL != queue);
		
	return (SListCount(queue));
}

/*Reveals the head element of the queue*/
void *QPeek(const queue_t *queue)
{
	assert(NULL != queue);
		
	return (SListGet(SListBegin(queue)));
}

/*Append 2 queues*/
void QAppend(queue_t *dest, queue_t *src)
{
	assert(NULL != dest);
	assert(NULL != src);
	
	SListAppend(dest, src);
}


