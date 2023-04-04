#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"

static int AddInt(element_t *element, int num_to_add)
{
	*((int*)&(element->val)) += num_to_add;
	
	return TRUE;
}

static int AddFloat(element_t *element, int num_to_add)
{
	*((float*)&(element->val)) += num_to_add;
	
	return TRUE;
}

static int AddString(element_t *element, int num_to_add)
{
	char copy[12];

	sprintf(copy, "%d", num_to_add);
	
	element->val = realloc(element->val, strlen(copy) + 1 + strlen(element->val));
	
	strcat((char*)element->val, copy);
	
	return (NULL == element->val) ? FAIL : TRUE;	
}

static void DoNothing(element_t *element)
{	
	UNUSED(element);
}

static void ClearStr(element_t *element)
{	
	free(element->val); 
}

static void PrintInt(element_t *element)
{
	printf("%d\n",*((int*)&(element->val)));
}

static void PrintFloat(element_t *element)
{
	printf("%f\n",*((float*)&(element->val)));
}

static void PrintStr(element_t *element)
{
	printf("%s\n",(char*)(element->val));
}


int CreateInt(element_t *element, int num)
{
	*((int*)&(element->val)) = num;
	element->add = AddInt;
	element->print = PrintInt;
	element->clean = DoNothing;
	
	return TRUE;
}

int CreateFloat(element_t *element, float num)
{
	*((float*)&(element->val)) = num;
	element->add = AddFloat;
	element->print = PrintFloat;
	element->clean = DoNothing;
	
	return TRUE;
}

int CreateString(element_t *element, char *str)
{
	element->val = (char*)(malloc(strlen(str) + 1)); 
	strcpy(element->val, str);
	
	element->add = AddString;
	element->print = PrintStr;
	element->clean = ClearStr;
	
	return (NULL == element->val) ? FAIL : TRUE;
}


void PrintAll(element_t *arr, size_t size)
{
	size_t i = 0; 
	
	for(i = 0; i < size; ++i)
	{
		arr[i].print(&arr[i]);
	}
}

void AddAll(element_t *arr, size_t size, int num_to_add)
{
	size_t i = 0; 
	
	for(i = 0; i < size; ++i)
	{
		arr[i].add(&arr[i],num_to_add);
	}
	
}

void CleanUpAll(element_t *arr, size_t size)
{
	size_t i = 0; 
	
	for(i = 0; i < size; ++i)
	{
		arr[i].clean(&arr[i]);
	}
	
}







