/*
Dev: BarSH
Rev: AnnaB
Date: 8.5.23
Status: Approved
*/

#include <stdlib.h>	/*malloc, free*/
#include <assert.h> /*assert*/

#include "sortlist.h"

#define TRUE (1)
#define FALSE (0)
#define UNUSED(x) ((void)(x))

struct SortList
{
	dlist_t *list;
	compare_t compare;
};

typedef struct is_to_insert_param
{
	compare_t compare;
	const void *data;
}is_to_insert_param_t;

/*Get's the dlist iterator inside the sortlist iterator*/
static dlist_iter_t GetDListIter(sort_iter_t current);

/*Set's the dlist iterator into a sortlist iterator*/
static sort_iter_t SetDListIter(sort_iter_t sr_iter, dlist_iter_t current);

/*A function that checks where we can insert a new node*/
static int IsToInsert(void *data, const void *param);

/*Creates a list*/
sort_list_t *SortListCreate(compare_t compare)
{
	sort_list_t *sort_list = (sort_list_t*)malloc(sizeof(sort_list_t));
	if (NULL == sort_list)
	{
		return (NULL);
	}
	
	sort_list->list = DListCreate();
	if (NULL == sort_list->list)
	{
		free(sort_list);
		return (NULL);
	}
	
	sort_list->compare = compare;
	
	return (sort_list);		
}

/*Erases a list*/
void SortListDestroy(sort_list_t *srlist)
{	
	assert(NULL != srlist);

	DListDestroy(srlist->list);
	free(srlist);
}

/*Inserts a new node to the list*/
sort_iter_t SortListInsert(sort_list_t *srlist, void *data)
{ 	
	sort_iter_t where = {NULL};
	is_to_insert_param_t param = {NULL}; 
	
	assert(NULL != srlist);
	
	param.compare = srlist->compare;
	param.data = data;
	
	#ifndef NDEBUG
	where.list = srlist; 
	#endif
	
	where = SortListFindIf(SortListBegin(srlist), SortListEnd(srlist),
						   IsToInsert, &param);

	DListInsert(GetDListIter(where), data);
	
	return (where);	 
}

/*Removes the node in the given iter*/
sort_iter_t SortListRemove(sort_iter_t current)
{
	current = SetDListIter(current, DListRemove(GetDListIter(current)));
	
	return (current);	 
}

/*Finds the position of the given value*/
sort_iter_t SortListFind(sort_iter_t from, sort_iter_t to, 
						 sort_list_t *srlist, void *param)
{
	sort_iter_t sr_iter = {NULL};
	
	assert(NULL != srlist);
	
	#ifndef NDEBUG
	assert(from.list == to.list);
	sr_iter.list = srlist; /*Add a check whether or not they are from the same list*/
	#endif
	
	sr_iter = SetDListIter(sr_iter, DListFind(GetDListIter(from), 
						   GetDListIter(to), srlist->compare, param));	
	 
	 return (sr_iter);
}

/*Conducts an operation on each node*/
int SortListForEach(sort_iter_t from, sort_iter_t to, 
					action_t action, void *action_param)
{
	assert(NULL != action);
	
	return (DListForEach(GetDListIter(from), GetDListIter(to), 
			action, action_param));		
}

/*Counts the number of nodes*/
size_t SortListSize(const sort_list_t *srlist)
{
	assert(NULL != srlist);
		
	return (DListSize(srlist->list));
}

/*Checks whether or not the sorted list is empty*/
int SortListIsEmpty(sort_list_t *srlist)
{
	assert(NULL != srlist);
	
	return (DListIsEmpty(srlist->list));
}

/*Get the tail of the list*/
sort_iter_t SortListEnd(const sort_list_t *srlist)
{	
	sort_iter_t sr_iter = {NULL};
	
	assert(NULL != srlist);
	
	sr_iter = SetDListIter(sr_iter, DListEnd(srlist->list));
	
	#ifndef NDEBUG
	sr_iter.list = (sort_list_t *)srlist; 
	#endif

	return (sr_iter);
}

/*Get the head of the list*/
sort_iter_t SortListBegin(const sort_list_t *srlist)
{
	sort_iter_t sr_iter = {NULL};
	
	assert(NULL != srlist);
	
	sr_iter = SetDListIter(sr_iter, DListBegin(srlist->list));
	
	#ifndef NDEBUG
	sr_iter.list = (sort_list_t *)srlist; 
	#endif

	return (sr_iter);
}

/*Get the value of the iter*/
void *SortListGetData(sort_iter_t current)
{
	return (DListGetData(GetDListIter(current)));
}

/*Get the next position of thee current iter*/
sort_iter_t SortListNext(sort_iter_t current)
{
	sort_iter_t sr_iter = {NULL};
	
	sr_iter = SetDListIter(sr_iter, DListNext(GetDListIter(current)));
	
	#ifndef NDEBUG
	sr_iter.list = current.list; 
	#endif

	return (sr_iter);
}

/*Get to the previous node*/
sort_iter_t SortListPrev(sort_iter_t current)
{
	sort_iter_t sr_iter = {NULL};
	
	sr_iter = SetDListIter(sr_iter, DListPrev(GetDListIter(current)));
	
	#ifndef NDEBUG
	sr_iter.list = current.list; 
	#endif

	return (sr_iter);
}


/*Removes a node from the end*/
void *SortListPopBack(sort_list_t *srlist)
{
	assert(NULL != srlist);
	
	return (DListPopBack(srlist->list));
}

/*Removes a node from the start*/
void *SortListPopFront(sort_list_t *srlist)
{
	assert(NULL != srlist);
	
	return (DListPopFront(srlist->list));
}

/*Checks whether or not 2 iters are equal*/
int SortListIsEqual(sort_iter_t iter1 , sort_iter_t iter2)
{
	return (DListIsEqual(GetDListIter(iter1),GetDListIter(iter2)));
}

/*Merges 2 lists*/
void SortListMerge(sort_list_t *dest, sort_list_t *src)
{
	sort_iter_t run_dest = {NULL};
	sort_iter_t run_src = {NULL};
	dlist_iter_t from = NULL;
	dlist_iter_t to = NULL;
	long int checker = 0;
	
	assert(NULL != dest);
	assert(NULL != src);
	assert(dest->compare == src->compare);

	run_dest = SortListBegin(dest); 
	run_src = SortListBegin(src);
	/*#ifndef NDEBUG
	run_dest.list = dest->list;
	run_dest.list = src->list; 
	#endif*/
	
	checker = dest->compare(SortListGetData(run_dest), 
							SortListGetData(run_src));
	
	while (!SortListIsEmpty(src) && NULL != GetDListIter(run_dest) && 
		   NULL != GetDListIter(run_src))
	{
		if (0 >= checker)
		{
			run_dest = SortListNext(run_dest);
			checker = dest->compare(SortListGetData(run_dest), 
									SortListGetData(run_src));
		}
		else
		{
			from = GetDListIter(run_src);
			
			while (0 < checker && NULL != DListNext(GetDListIter(run_src)))
			{
				run_src = SortListNext(run_src);
				checker = dest->compare(SortListGetData(run_dest), 
										SortListGetData(run_src));
			}
			
			to = GetDListIter(run_src);
			
			DListSplice(GetDListIter(run_dest), from, to); 	
		}
	}
}

/*Checks whether a value is in the list*/
sort_iter_t SortListFindIf(sort_iter_t from, sort_iter_t to,
						   is_match_t is_match, void* param)
{
	sort_iter_t from_iter_runner = {NULL};
	
	assert(is_match);

	#ifndef NDEBUG
	assert(from.list == to.list);
	#endif /*NDEBUG*/
	
	from_iter_runner = SetDListIter(from_iter_runner, 
									DListFind(GetDListIter(from), 
									GetDListIter(to), is_match, param));
	
	return (from_iter_runner);
}


static dlist_iter_t GetDListIter(sort_iter_t current)
{
	return (current.iter);
}

static sort_iter_t SetDListIter(sort_iter_t sr_iter, dlist_iter_t current)
{
	sr_iter.iter = current;
	
	return (sr_iter);
}

static int IsToInsert(void *data, const void *param)
{
	compare_t compare = ((is_to_insert_param_t *)param)->compare;
	const void *param_data = ((is_to_insert_param_t *)param)->data;
		
	return (0 <= compare(data, param_data));
}




