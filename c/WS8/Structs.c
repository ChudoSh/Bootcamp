#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*strlen, strcat*/
#include <assert.h> /*assert*/

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
	char *temp = NULL; 
	
	assert(NULL != element);

	sprintf(copy, "%d", num_to_add);
	
	temp = realloc(element->val, strlen(copy) + 1 + strlen(element->val));
	
	if(NULL == temp)
	{
		return FAILMEMORY;
	}	
	
	strcat((char*)temp, copy);
	
	element->val = temp;
	
	return TRUE;	
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
	assert(NULL != arr);	
	
	printf("%s\n",(char*)(element->val));
}


int CreateInt(element_t *element, int num)
{
	assert(NULL != element);
	
	*((int*)&(element->val)) = num;
	element->add = AddInt;
	element->print = PrintInt;
	element->clean = DoNothing;
	
	return TRUE;
}

int CreateFloat(element_t *element, float num)
{
	assert(NULL != element);
	
	*((float*)&(element->val)) = num;
	element->add = AddFloat;
	element->print = PrintFloat;
	element->clean = DoNothing;
	
	return TRUE;
}

int CreateString(element_t *element, char *str)
{
	assert(NULL != element);
	
	element->val = (char*)(malloc(strlen(str) + 1)); 
	
	if(NULL == element->val)
	{
		return FAILMEMORY;
	} 
	
	strcpy(element->val, str);
	
	element->add = AddString;
	element->print = PrintStr;
	element->clean = ClearStr;
	
	return TRUE;
}


void PrintAll(element_t *arr, size_t size)
{
	
	assert(NULL != arr);	
	
	size_t i = 0; 
	
	for(i = 0; i < size; ++i)
	{
		arr[i].print(&arr[i]);
	}
}

int AddAll(element_t *arr, size_t size, int num_to_add)
{

	assert(NULL != arr);
	
	size_t i = 0; 
	
	for(i = 0; i < size; ++i)
	{
		if(FAIL == arr[i].add(&arr[i],num_to_add))
		{
			return FAIL;
		}
	}
	
	return TRUE;	
}

void CleanUpAll(element_t *arr, size_t size)
{
	assert(NULL != arr);
	
	size_t i = 0; 
	
	for(i = 0; i < size; ++i)
	{
		arr[i].clean(&arr[i]);
	}	
}







