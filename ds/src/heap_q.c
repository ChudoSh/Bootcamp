/*
Dev: BarSH
Rev: 
Date: 20.6.23
Status: 
*/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */

#include "heap_q.h" 

enum STATUS
{
    FAIL = -1, 
    SUCCESS = 0
};

struct PQueue
{
	heap_t *heap; 
};

static heap_t *GetHeap(const pq_t *pq);

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
	
	pqueue->heap = HeapCreate(compare);
	if (NULL == pqueue->heap)
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
	
	HeapDestroy(GetHeap(pq));
	free(pq);
}

/*Insert a new node into the pqueue*/
int PQEnqueue(pq_t *pq, void *data)
{
	assert(NULL != pq);
	
	return (HeapPush(GetHeap(pq), data));
}

/*Removes the node with the least priority*/
void *PQDequeue(pq_t *pq)
{
    void *removed = NULL; 

	assert(NULL != pq);
	assert(!PQIsEmpty(pq));

    removed = HeapPeek(GetHeap(pq));
    HeapPop(GetHeap(pq));
	
	return (removed);
}

/*Gets the value of the most significant node*/
void *PQPeek(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (HeapPeek(GetHeap(pq)));
}

/*Erases a node in the pqueue given its element*/
void *PQErase(pq_t *pq, int (*is_match)(const void *, const void *), void *param)
{
	assert(NULL != pq);
	assert(NULL != is_match);
	assert(!PQIsEmpty(pq));
			  
	return (HeapRemove(GetHeap(pq), param, is_match));
}

/*Empties the queue*/ 
void PQClear(pq_t *pq)
{
	assert(NULL != pq);
	
	while (!HeapIsEmpty(GetHeap(pq)))
	{
		HeapPop(GetHeap(pq));
	}
}

/*Count elements in the queue*/ 
size_t PQSize(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (HeapSize(GetHeap(pq)));
}

/*Checks if the pqueue is empty*/
int PQIsEmpty(const pq_t *pq)
{
	assert(NULL != pq);
	
	return (HeapIsEmpty(GetHeap(pq)));
}

/*========Statis funcs=========*/

/*Gettes and setter*/

static heap_t *GetHeap(const pq_t *pq)
{
    return (pq->heap);
}
