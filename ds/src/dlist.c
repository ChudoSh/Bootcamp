/*
Dev: BarSH
Rev: Eylon
Status: Approved
Date: 7.5.23
*/

#include <stdlib.h>	/*malloc, free*/
#include <assert.h> /*assert*/

#include <stdio.h>

#include "dlist.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (1)
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

/*Sets the next address of the current node to the given position*/
static void DListSetNext(dlist_iter_t current, dlist_iter_t next_pos);

/*Sets the previous address of the current node to the given position*/
static void DListSetPrev(dlist_iter_t current, dlist_iter_t p_pos);

/*Sets the next and previous addresses of the current node to the given positions*/
static void DListSetPosition(dlist_iter_t current, dlist_iter_t next, 
							 dlist_iter_t prev);

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
	
	list->head.next  = &(list->tail);
	list->head.previous = NULL; 
	
	list->tail.previous = &(list->head);
	list->tail.next = NULL;
	
	return (list);		
}

/*Erases a list*/
void DListDestroy(dlist_t *list)
{	
	assert(NULL != list);

	while (TRUE != DListIsEmpty(list))
	{
		DListPopFront(list);
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
		while (NULL != DListNext(where))
		{
			where = DListNext(where);
		}
		
		return (where);
	}
	
	DListSetData(insert, data);
	DListSetPosition(insert, where, DListPrev(where));
	
	DListSetNext(DListPrev(insert), insert);
	DListSetPrev(DListNext(insert), insert);
	
	return (insert);	 
}

/*Removes the node in the given iter*/
dlist_iter_t DListRemove(dlist_iter_t current)
{
	dlist_iter_t save = NULL;

	assert(NULL != current);
	assert(NULL != DListNext(current));
	
	save = DListNext(current);

	/*Set the previous of the next to current to the previous of current*/
	DListSetPrev(save, DListPrev(current));
	/*Set the next of the previous to current to the next of current*/
	DListSetNext(DListPrev(current), save);

	free(current);
	
	return (save);	 
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
int DListForEach(dlist_iter_t from, dlist_iter_t to, int(*action_func)(void *data, 
				 void *param), void *action_param)
{
	int status = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	
	while (from != to)
	{
		status = action_func(DListGetData(from), action_param); 
		
		if (SUCCESS != status)
		{
			return (status);
		}
		
		from = DListNext(from);
	}
	
	return (TRUE);		
}

/*Finds the position of the given value*/
dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, 
					   int (*match_func)(void *data, const void *param), 
					   const void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	
	while (!DListIsEqual(from, to) && !match_func(DListGetData(from), param))
	{
		from = DListNext(from);
	}
	
	return (from);
}

/*Get the tail of the list*/
dlist_iter_t DListEnd(const dlist_t *list)
{	
	assert(NULL != list);
	
	return (&((dlist_t *)list)->tail);
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
int DListIsEqual(dlist_iter_t iter1 , dlist_iter_t iter2)
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
	void *data = NULL;

	assert(NULL != list);
	
	data = DListGetData(DListPrev(DListEnd(list)));
	
	DListRemove(DListPrev(DListEnd(list)));

	return (data);
}

/*Removes a node from the end*/
void *DListPopFront(dlist_t *list)
{
	void *data = NULL;
	
	assert(NULL != list);
	
	data = DListGetData(DListBegin(list));
	
	DListRemove(DListBegin(list));
	
	return (data);
}

/*Checks whether the list is empty*/
int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);
	
	return (DListIsEqual(DListEnd(list),DListBegin(list)));
}

/*Appends a part of given list to another*/
dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	dlist_iter_t temp = NULL;
	 
	assert(NULL != where);
	assert(NULL != from);
	assert(NULL != to);
	
	temp = DListPrev(from);
	
	DListSetNext(DListPrev(where), from);
	DListSetPrev(from, DListPrev(where));
	
	DListSetNext(DListPrev(to), where);
	DListSetPrev(where, DListPrev(to));
	
	DListSetNext(temp, to);
	DListSetPrev(to, temp);
	
	return (where);
}
	

int DListMultiFind(dlist_iter_t from, dlist_iter_t to, 
				   int (*match_func)(void *data, const void *param), 
				   const void *param, dlist_t *output_list)
{
	dlist_iter_t runner = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	assert(NULL != output_list);
	
	runner = from;
	
	while (runner != to)
	{
		runner = DListFind(runner, to, match_func, param);
		if (runner == to)
		{
			return (TRUE);
		}
		
		if (DListEnd(output_list) == DListPushBack(output_list, 
												   DListGetData(runner)))
		{
			return (FALSE);
		}
		
		runner = DListNext(runner);
	}

	return (TRUE);
}

/*A count function*/
static int GetSize(void *a, void *b)
{
	++(*(size_t *)b);
	
	UNUSED(a);
	
	return (SUCCESS);		
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

static void DListSetNext(dlist_iter_t current, dlist_iter_t next_pos)
{
	assert(NULL != current);
	
	current->next = next_pos;
}

static void DListSetPrev(dlist_iter_t current, dlist_iter_t previous_pos)
{
	assert(NULL != current);
	
	current->previous = previous_pos;
}

static void DListSetPosition(dlist_iter_t current, dlist_iter_t next, 
							 dlist_iter_t prev)
{
	assert(NULL != current);
	
	DListSetNext(current, next);
	DListSetPrev(current, prev);
}

