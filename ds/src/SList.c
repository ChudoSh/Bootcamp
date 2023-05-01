/*
Dev: BarSH
Rev: 
Date: 1.5.23
Status: 
*/ 

#include <stdlib.h>	/*malloc, free*/
#include <assert.h> /*assert*/

#include "SList.h"

#define SUCCESS (1)

struct Node
{	
	void *value;
	node_t *next;
};

struct SList
{
	node_t *head;
	node_t *tail;
};

static void *Count(void *a, void *b);

/*Creates a list*/
slist_t *SListCreate(void)
{
	node_t *dummy = NULL;
	
	slist_t *list = (slist_t*)malloc(sizeof(slist_t));
	
	if (NULL == list)
	{
		return (NULL);
	}
	
	dummy = (node_t*)malloc(sizeof(node_t));
	
	if (NULL == dummy)
	{	
		free(list);
		return (NULL);
	} 

	dummy->value = list;
	dummy->next = NULL; 
	
	list->head = dummy;
	list->tail = dummy;
	
	return (list);		
}

/*Erases a list*/
void SListDestroy(slist_t *list)
{	
	assert(NULL != list);

	while (SListEnd(list) != SListBegin(list))
	{
		SListRemove(SListBegin(list));
	}
	
	free(SListEnd(list));
	free(list);
	list = NULL;
}

/*Inserts a new node*/
iter_t SListInsert(iter_t where, void *value)
{
	iter_t insert = NULL;

	assert(NULL != where);
	assert(NULL != value);
	
	insert = (node_t*)malloc(sizeof(node_t));
	
	if (NULL == insert)
	{
		return (NULL);
	}
	
	SListSet(insert, SListGet(where));
	insert->next = SListNext(where);
	 
	SListSet(where, value);
	where->next = insert;
	
	if (NULL == (insert->next))
	{
		((slist_t *)insert->value)->tail = insert;  
	}
	
	return (where);	 
}

/*Removes the node in the given iter*/
iter_t SListRemove(iter_t where)
{
	iter_t remove = NULL;

	assert(NULL != where);

	remove = SListNext(where);
	SListSet(where, SListGet(where->next));
	where->next = SListNext(where->next);
	
	if (NULL == (where->next))
	{
		((slist_t *)where->value)->tail = where;  
	}
	
	free(remove);
	
	return (where);	 
}

/*Counts the number of nodes*/
size_t SListCount(const slist_t *list)
{
	size_t count = 0; 
	
	assert(NULL != list);
	
	SListForEach(SListBegin(list), SListEnd(list), Count, &count);
		
	return (count);
}

/*Conducts an operation on each node*/
void SListForEach(iter_t from, iter_t to, action_t action, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != param);
	assert(NULL != action);
	
	while (SUCCESS != SListIterIsEqual(from, to))
	{
		action(SListGet(from), param);
		from = SListNext(from);
	}
		
}

/*Finds the position of the given value*/
iter_t SListFind(iter_t from, iter_t to, const void *value, is_match_t matcher)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != value);
	assert(NULL != matcher);
	
	while (SUCCESS != SListIterIsEqual(from, to))
	{
		if	(SUCCESS == matcher(value, SListGet(from)))
		{
			return (from);
		}
		
		from = SListNext(from);
	}
	
	return (to);
}

/*Get the tail of the list*/
iter_t SListEnd(const slist_t *list)
{	
	assert(NULL != list);
	
	return (list->tail);
}

/*Get the head of the list*/
iter_t SListBegin(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->head);
}

/*Set the value of the iter to the given value*/
void SListSet(iter_t position, void *value)
{
	assert(NULL != position);
		
	position->value = value;
}

/*Get the value of the iter*/
void *SListGet(iter_t position)
{
	assert(NULL != position);
		
	return (position->value);
}

/*Are the iters equal?*/
int SListIterIsEqual(iter_t iter1 , iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

/*Get the next position of thee current iter*/
iter_t SListNext(iter_t position)
{
	assert(NULL != position);
	
	return (position->next);
}

static void *Count(void *a, void *b)
{
	++(*(size_t *)b);
	
	return (a);
}


