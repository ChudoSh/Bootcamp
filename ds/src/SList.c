/*
Dev: BarSH
Rev: 
Date: 
Status: 
*/ 

#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*memcpy*/
#include <assert.h> /*assert*/
#include <stdio.h>

#include "SList.h"

 
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
		return (NULL);
	} 

	dummy->value = &(list->tail);
	dummy->next = NULL; 
	
	list->head = dummy;
	list->tail = dummy;
	
	return (list);		
}

/*Erases a list*/
void SListDestroy(slist_t *list)
{
	iter_t temp1 = NULL; 
	iter_t temp2 = NULL;
	
	assert(NULL != list);
	
	temp1 = list->head;

	while (list->tail != temp1)
	{
		temp2 = temp1->next; 
		free(temp1);
		temp1 = temp2;
	}
	
	free(list->tail);
	list->tail = NULL;
	
	free(list);
	list = NULL;
}

iter_t SListInsert(iter_t where, void *value)
{
	node_t *insert = NULL;

	assert(NULL != where);
	
	insert = (node_t*)malloc(sizeof(node_t));
	
	if (NULL == insert)
	{
		return (NULL);
	}
	
	insert->value = where->value;
	insert->next = where->next; 
	where->value = value;
	where->next = insert;
	
	if (NULL == (insert->next))
	{
		*((node_t**)(insert->value)) = insert;  
	}
	
	return (where);	 
}

iter_t SListEnd(const slist_t *list)
{	
	assert(NULL != list);
	
	return (list->tail);
}

iter_t SListBegin(const slist_t *list)
{
	assert(NULL != list);
	
	return (list->head);
}

void SListSet(iter_t position, void *value)
{
	assert(NULL != position);
		
	position->value = value;
}

void *SListGet(iter_t position)
{
	assert(NULL != position);
		
	return (position->value);
}

int SListIterIsEqual(iter_t iter1 , iter_t iter2)
{
	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

iter_t SListNext(iter_t position)
{
	assert(NULL != position);
	
	return (position->next);
}



