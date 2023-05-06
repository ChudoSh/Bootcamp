/*
Dev: BarSH
Rev: 
Date: 5.5.23
Status: 
*/

#include <stdlib.h>	/*malloc, free*/
#include <assert.h> /*assert*/

#include "dlist.h"

#define TRUE (1)
#define FALSE (0)
#define UNUSED(x) ((void)(x))



struct Node
{	
	void *value;
	node_t *next;
	node_t *previous;
};

struct DList
{
	node_t head;
	node_t tail;
};

/*A count function*/
static int GetSize(void *a, void *b);

/*Creates a node*/
static node_t *CreateNode();

/*Creates a list*/
dlist_t *DListCreate(void)
{
	dlist_t *list = (dlist_t*)malloc(sizeof(dlist_t));
	if (NULL == list)
	{
		return (NULL);
	}
	
	DListSetData(&(list->head), list);
	DListSetData(&(list->tail), list);
	
	list->head.next = &(list->tail);
	list->tail.previous = &(list->head);
	
	list->head.previous = NULL; 
	list->tail.next = NULL;
	
	return (list);		
}

/*Erases a list*/
void DListDestroy(dlist_t *list)
{	
	assert(NULL != list);

	while (DListEnd(list) != DListBegin(list))
	{
		DListRemove(DListBegin(list));
	}
	
	free(list);
}

/*Inserts a new node*/
dlist_iter_t DListInsert(dlist_iter_t where, void *data)
{
	dlist_iter_t insert = NULL;

	assert(NULL != where);
	
	insert = CreateNode();
	
	if (NULL == insert)
	{	
		while (NULL != where)
		{
			where = DListNext(where);
		}
		
		return (where);
	}
	
	DListSetData(insert, data);
	insert->next = where;
	insert->previous = DListPrev(where);
	
	insert->previous->next = insert;
	insert->next->previous = insert;
	
	return (DListPrev(where));	 
}

/*Removes the node in the given iter*/
dlist_iter_t DListRemove(dlist_iter_t current)
{
	dlist_iter_t remove = NULL;

	assert(NULL != current);

	remove = DListNext(current);
	current->next->previous = DListPrev(current);
	current->previous->next = DListNext(current);

	free(current);
	
	return (remove);	 
}

/*Counts the number of nodes*/
size_t DListSize(const dlist_t *list)
{
	size_t size = 0; 
	
	assert(NULL != list);
	
	DListForEach(DListBegin(list), DListEnd(list), GetSize, &size);
		
	return (size);
}

/*Conducts an operation on each node*/
int DListForEach(dlist_iter_t from, dlist_iter_t to, int(*action_func)(void *data, void *param), void *action_param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	
	while (from != to)
	{
		if (TRUE != action_func(DListGetData(from), action_param))
		{
			return (FALSE);
		}
		
		from = DListNext(from);
	}
	
	return (TRUE);		
}

/*Finds the position of the given value*/
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, int (*match_func)(void *data, const void *param), const void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	assert(NULL != param);
	
	while (from != DListNext(to))
	{
		if	(TRUE == match_func(DListGetData(from), param))
		{
			return (from);
		}
		
		from = DListNext(from);
	}
	
	return (to);
}

/*Get the tail of the list*/
dlist_iter_t DListEnd(const dlist_t *list)
{	
	assert(NULL != list);
	
	return (&(((dlist_t *)list))->tail);
}

/*Get the head of the list*/
dlist_iter_t DListBegin(const dlist_t *list)
{
	assert(NULL != list);
	
	return (((dlist_t *)list)->head.next);
}

/*Set the value of the iter to the given value*/
void DListSetData(dlist_iter_t current, void *value)
{
	assert(NULL != current);
		
	current->value = value;
}

/*Get the value of the iter*/
void *DListGetData(dlist_iter_t current)
{
	assert(NULL != current);
		
	return (current->value);
}

/*Are the iters equal?*/
int DListIterIsEqual(dlist_iter_t iter1 , dlist_iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

/*Get the next position of thee current iter*/
dlist_iter_t DListNext(dlist_iter_t current)
{
	assert(NULL != current);
	
	return (current->next);
}

/*Get to the next node*/
dlist_iter_t DListPrev(dlist_iter_t current)
{
	assert(NULL != current);
	
	return (current->previous);
}

/*Inserts a node from the end*/
dlist_iter_t DListPushBack(dlist_t *list, void *data)
{
	assert(NULL != list);
	
	return (DListInsert(DListEnd(list), data));
}

/*Inserts a node from the start*/
dlist_iter_t DListPushFront(dlist_t *list, void *data)
{
	assert(NULL != list);
	
	return (DListInsert(DListBegin(list), data));
}

/*Removes a node from the start*/
void *DListPopBack(dlist_t *list)
{
	assert(NULL != list);
	
	return (DListRemove(DListPrev(DListEnd(list))));
}

/*Removes a node from the end*/
void *DListPopFront(dlist_t *list)
{
	assert(NULL != list);
	
	return (DListRemove(DListBegin(list)));
}

int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);
	
	return (DListIterIsEqual(DListEnd(list),DListBegin(list)));
}

dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	assert(NULL != where);
	assert(NULL != from);
	assert(NULL != to);
	
	DListPrev(from)->next = to;
	
	DListPrev(to)->next = DListNext(where);
	DListNext(where)->previous = DListPrev(to);
	
	where->next = from;
	from->previous = where;
	
	to->previous = from;
	
	return (where);
}
	

int DListMultiFind(dlist_iter_t from, dlist_iter_t to, int (*match_func)(void *data, const void *param), const void *param, dlist_t *output_list)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	assert(NULL != output_list);
	
	while (from != to)
	{
		if	(from == DListFind(from, to, match_func, param))
		{
			if (from != DListPushBack(output_list, (void *)param))
			{
				return (FALSE);
			}
		}
		
		from = DListNext(from);
	}
	
	return (TRUE);
}


/*A count function*/
static int GetSize(void *a, void *b)
{
	++(*(size_t *)b);
	
	UNUSED(a);
	
	return (TRUE);		
}

/*Creates a new node*/
static node_t *CreateNode()
{
	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	
	if (NULL == new_node)
	{		
		return (NULL);
	}
	
	DListSetData(new_node, NULL);
	new_node->next = NULL;
	new_node->previous = NULL;
	
	return (new_node);
}


