/*
Dev: BarSH
Rev: Michal
Date: 4.5.23
Status: Fixed
*/

#include <stdlib.h>	/*malloc, free*/
#include <assert.h> /*assert*/

#include "slist.h"

#define TRUE (1)
#define IS_EMPTY (0)
#define UNUSED(x) ((void)x)

enum RESULT 
{
	FAIL = -1, 
	SUCCESS = 0
};

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

/*A count function*/
static int Count(void *a, void *b);

/*Creates a node*/
static node_t *CreateNode();

/*Creates a list*/
slist_t *SListCreate(void)
{
	node_t *dummy = NULL;	
	
	slist_t *list = (slist_t*)malloc(sizeof(slist_t));
	
	if (NULL == list)
	{
		return (NULL);
	}
	
	dummy = CreateNode();
	
	if (NULL == dummy)
	{	
		free(list);
		return (NULL);
	} 

	SListSet(dummy, list);
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
}

/*Inserts a new node*/
iter_t SListInsert(iter_t where, void *value)
{
	iter_t insert = NULL;

	assert(NULL != where);
	
	insert = CreateNode();
	
	if (NULL == insert)
	{	
		while (NULL != where)
		{
			where = SListNext(where);
		}
		
		return (where);
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
int SListForEach(iter_t from, iter_t to, action_t action, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action);
	
	while (TRUE != SListIterIsEqual(from, to))
	{
		action(SListGet(from), param);
		from = SListNext(from);
	}
	
	if (TRUE != SListIterIsEqual(from, to))
	{
		return (FAIL);
	}
	
	return (SUCCESS);		
}

/*Finds the position of the given value*/
iter_t SListFind(iter_t from, iter_t to, const void *value, is_match_t matcher)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != matcher);
	
	while (TRUE != SListIterIsEqual(from, to))
	{
		if	(TRUE == matcher(value, SListGet(from)))
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

/*Get the next position of thee current iter*/
void SListAppend(slist_t *dest, slist_t *src)
{	
	assert(NULL != dest);
	assert(NULL != src);
	
	if (IS_EMPTY == SListCount(src))
	{
		return;
	}
	
	dest->tail->value = src->head->value;
	dest->tail->next = src->head->next; 
	
	src->tail->value = dest;
	dest->tail = src->tail;
	
	src->head->value = src;
	src->head->next = NULL;
	src->tail = src->head;
}

static int Count(void *a, void *b)
{
	++(*(size_t *)b);
	
	UNUSED(a);
	
	return (SUCCESS);		
}

static node_t *CreateNode()
{
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	
	if (NULL == new_node)
	{		
		return (NULL);
	}
	
	SListSet(new_node, NULL);
	new_node->next = NULL;
	
	return (new_node);
}


