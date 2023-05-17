/*
Dev: BarSH
Rev: LeonG
Date: 17.5.23
Status: Approved
*/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "pqueue.h" 

#define FAIL (-1)
#define SUCCESS (0)

struct PQueue
{
	sort_list_t *list; 
};

/*Create a priority queue.*/
pq_t *PQCreate(int (*compare)(const void *,const void *))
{
	pq_t *pqueue = NULL;
	
	assert(NULL != compare);
	
	pqueue = (pq_t *)(malloc(sizeof(pq_t)));
	if (NULL == pqueue)
	{
		return (NULL);
	}
	
	pqueue->list = SortListCreate((compare_t)compare);
	if (NULL == pqueue->list)
	{
		free(pqueue);
		return (NULL);
	}
	
	return (pqueue);
}

/*Destroys a priority queue.*/
void PQDestroy(pq_t *pq)
{
	assert(NULL != pq);
	
	SortListDestroy(pq->list);
	free(pq);
}

/*Insert a new node into the pqueue*/
int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	if (SortListIsEqual(SortListEnd(pq->list), SortListInsert(pq->list, data)))
	{
		return (FAIL);
	}
	
	return (SUCCESS);
}

/*Removes the node with the least priority*/
void *PQDequeue(pq_t *pq)
{
	void *value = NULL;
	
	assert(NULL != pq);
	
	value = SortListPopFront(pq->list);
	
	return (value);
}

/*Gets the value of the most significant node*/
void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortListGetData(SortListPrev(SortListEnd(pq->list))));
}

/*Erases a node in the pqueue given its element*/
int PQErase(pq_t *pq, int (*is_match)(const void *, const void *), void *param)
{
	assert(NULL != pq);
	assert(NULL != is_match);
		
	if (SortListIsEqual(SortListFindIf(SortListBegin(pq->list), 
				   		SortListEnd(pq->list), (is_match_t)is_match, param), 
				   		SortListEnd(pq->list)))
	{
		return (FAIL);
	}
				   
	SortListRemove(SortListFindIf(SortListBegin(pq->list), 
				   SortListEnd(pq->list), (is_match_t)is_match, param));
	
	return (SUCCESS);
}

/*Empties the queue*/ 
void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (!SortListIsEmpty(pq->list))
	{
		SortListPopFront(pq->list);
	}
}

/*Count elements in the queue*/ 
size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortListSize(pq->list));
}

/*Checks if the pqueue is empty*/
int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (SortListIsEmpty(pq->list));
}

