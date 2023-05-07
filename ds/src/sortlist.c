/*
Dev: BarSH
Rev: 
Date: 5.5.23
Status: 
*/

#include <stdlib.h>	/*malloc, free*/
#include <assert.h> /*assert*/

#include "sortlist.h"
#include "dlist.h"

#define TRUE (1)
#define FALSE (0)
#define UNUSED(x) ((void)(x))


/*A count function*/
static int GetSize(void *a, void *b);

/*Creates a node*/
static node_t *CreateNode();

/*Sets the next address of the current node*/
static void DListSetNext(dlist_iter_t current, dlist_iter_t next_pos);

/*Sets the previous address of the current node*/
static void DListSetPrev(dlist_iter_t current, dlist_iter_t p_pos);

/*Sets the next and previous addresses of the current node*/
static void DListSetPosition(dlist_iter_t current, dlist_iter_t next, dlist_iter_t prev);

/*Creates a list*/
sort_list_t *SortListCreate(compare_t);
{
	sort_list_t *sort_list = (sort_list_t*)malloc(sizeof(sort_list_t));
	if (NULL == sort_list)
	{
		return (NULL);
	}
	
	sort_list.list = DListCreate();
	if (NULL == sort_list.list)
	{
		return (NULL);
	}
	
	sort_list.compare = compare_t;
	
	return (list);		
}

/*Erases a list*/
void SortListDestroy(sort_list_t *list)
{	
	assert(NULL != list);

	while (SortListEnd(list) != SortListBegin(list))
	{
		SortListRemove(SortListBegin(list));
	}
	
	free(list);
}

/*Inserts a new node*/
sort_iter_t SortListInsert(sort_list_t *list, void *data)
{
	sort_iter_t insert = NULL;

	assert(NULL != where);
	
	insert = CreateNode();
	
	if (NULL == insert)
	{	
		while (NULL != where)
		{
			where = SortListNext(where);
		}
		
		return (where);
	}
	
	DListSetData(insert, data);
	DListSetPosition(insert, where,DListPrev(where));
	
	DListSetNext(DListPrev(insert), insert);
	DListSetPrev (DListNext(insert), insert);
	
	return (where);	 
}

/*Removes the node in the given iter*/
dlist_iter_t DListRemove(dlist_iter_t current)
{
	dlist_iter_t remove = NULL;

	assert(NULL != current);
	
	if (NULL == DListPrev(DListPrev(current)))
	{
		remove = DListNext(current);
	}
	else
	{	
		remove = DListPrev(current);
	}
	
	DListSetPrev(DListNext(current), DListPrev(current));
	DListSetNext(DListPrev(current), DListNext(current));

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

int DListIsEmpty(const dlist_t *list)
{
	assert(NULL != list);
	
	return (DListIsEqual(DListEnd(list),DListBegin(list)));
}

dlist_iter_t DListSplice(dlist_iter_t where, dlist_iter_t from, dlist_iter_t to)
{
	assert(NULL != where);
	assert(NULL != from);
	assert(NULL != to);
	
	DListSetNext(DListPrev(from), to);
	
	DListPrev(to)->next = DListNext(where);
	DListSetPrev(DListNext(where), DListPrev(to));
	
	DListSetNext(where, from);
	DListSetPrev(from, where);
	
	DListSetPrev(to, from);
	
	return (where);
}
	

int DListMultiFind(dlist_iter_t from, dlist_iter_t to, int (*match_func)(void *data, const void *param), const void *param, dlist_t *output_list)
{
	dlist_iter_t runner = NULL;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	assert(NULL != output_list);
	
	runner = from;
	
	while (from != to)
	{
		if (runner == DListFind(runner, to, match_func, param))
		{
			return (FALSE);
		}
		
		if (DListEnd(output_list) == DListPushFront(output_list, runner))
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

static void DListSetPosition(dlist_iter_t current, dlist_iter_t next, dlist_iter_t prev)
{
	assert(NULL != current);
	
	DListSetPrev(current, prev);
	DListSetNext(current, next);
}
