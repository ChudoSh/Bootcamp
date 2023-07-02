/*
Dev : BarSh
Rev:
Date: 9.6.23
Status:
*/

#include <stdio.h>
#include <assert.h>


#include "stack.h"
#include "recursion.h"

static stack_t *RecursiveSort(stack_t *unsorted, stack_t *to_sort);
static node_t *RecursiveFlip(node_t *head, node_t *current);


int Fibonnachi(int element_index)
{   
    if (element_index <= 1)
    {
        return (element_index);
    }

    return (Fibonnachi(element_index - 1) + Fibonnachi(element_index - 2));
}

node_t *FlipRec(node_t *head)
{	
	return (RecursiveFlip(NULL, head)); 
}

stack_t *SortStack(stack_t *unsorted, size_t capacity)
{
    stack_t *to_sort = NULL; 

    assert(NULL != unsorted);

    to_sort = StackCreate(capacity, sizeof(int));
    if (NULL == to_sort)
    {
        return (NULL);
    }
    
    StackPush(to_sort, StackPeek(unsorted));
    StackPop(unsorted);

    return (RecursiveSort(unsorted, to_sort));   
}

size_t Strlen(char *str)
{ 
    if ('\0' == *str)
    {
        return (0);
    }

    return (1 + Strlen(++(str))); 
}

int Strcmp(char *dest, char *src)
{ 
    if (*dest != *src)
    {
        return (*dest - *src);
    }

    if ('\0' == *dest)
    {
        return (0);
    }

    return (Strcmp(++(dest), ++(src))); 
}

char *Strcpy(char *dest, char *src)
{ 
    assert(NULL != dest);
    assert(NULL != src);
    
    if ('\0' == *src)
    {
        *dest = '\0';
        return (dest);
    }

    *dest = *src; 

    return (Strcpy(++(dest), ++(src))); 
}


char *Strcat(char *dest, char *src)
{ 
    assert(NULL != dest);
    assert(NULL != src);

    if ('\0' == *dest)
    {
        return (Strcpy(dest, src));
    }

    return (Strcat(++(dest), src)); 
}

char *Strstr(char *haystack, char *needle)
{ 
    assert(NULL != haystack);
    assert(NULL != needle);

    if ('\0' == *needle)
    {
        return ((char *)haystack);
    }

    if ('\0' == *haystack)
    {
        return (NULL);
    }

    if (*haystack == *needle)
    {
        return (Strstr(haystack + 1, needle + 1));
    }

    return Strstr(haystack + 1, needle);
}

/******************Static functions********************************************/
static node_t *RecursiveFlip(node_t *head, node_t *current)
{
    node_t *forward = NULL;

    if (NULL == current)
	{
		return (head);
	}

    forward = current->next;
    current->next = head;
    head = current;
    current = forward;

    return (RecursiveFlip(head, current));
}

static stack_t *RecursiveSort(stack_t *unsorted, stack_t *to_sort)
{
    int temp = *(int*)StackPeek(to_sort); 

    if (StackIsEmpty(unsorted))
    {
        StackDestroy(unsorted);
        return (to_sort);
    }

    if (*(int *)StackPeek(unsorted) <= temp)
    {
        StackPush(to_sort, StackPeek(unsorted));
        StackPop(unsorted);
    }

    else
    {
        temp = *(int *)StackPeek(unsorted);
        StackPop(unsorted);
        StackPush(unsorted, StackPeek(to_sort));
        StackPop(to_sort);
        StackPush(unsorted, &temp);
    }

    return (RecursiveSort(unsorted, to_sort));
}  
