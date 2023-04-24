/*
Dev: BarSH
Rev: 
Date: 23.4.23
Status: 
*/ 

#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*memcpy*/
#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/

#include "D_Vector.h"

 
enum RESULT
{
	FAIL = -1, 
	SUCCESS = 0
};	

struct DVector
{
	size_t size;
	size_t capacity;
	size_t element_size;
	char *base_ptr;
};

/*Creates the vector*/
dvector_t *DVectorCreate(size_t element_size, size_t capacity)
{
	dvector_t *vector = (dvector_t*)malloc(sizeof(dvector_t));
	vector->base_ptr = (char*)(malloc(element_size * capacity));
	
	if (NULL == vector)
	{
		return (NULL);
	}
	
	if (NULL == vector->base_ptr)
	{
		free(vector);
		vector = NULL;
		return (NULL);
	
	}
	
	vector->capacity = capacity;
	vector->size = 0;
	vector->element_size = element_size;
	
	return (vector);	
}

/*Erases the vector*/
void DVectorDestroy(dvector_t *vector)
{
	assert(NULL != vector);
	
	free(vector->base_ptr);
	vector->base_ptr = NULL;
	free(vector);
	vector = NULL;	
}

/*Adds an element to the vector*/
int DVectorPushBack(dvector_t *vector, const void *element)
{
	assert(NULL != vector);
	assert(NULL != element);
	
	if (vector->capacity == vector->size)
	{
		vector->capacity *= 2;
		
		vector->base_ptr = (char*)realloc((void*)vector->base_ptr, (vector->element_size * vector->capacity));
		
		if (NULL == vector->base_ptr)
		{
			free(vector);
			vector = NULL;
			return (FAIL);
		}
	
	}
	
	if (NULL == memcpy(vector->base_ptr + (vector->element_size * vector->size), element, vector->element_size))
	{
		return (FAIL);
	}
		
	++vector->size;
	
	return (SUCCESS);
}

/*Removes the top element of the vector*/
int DVectorPopBack(dvector_t *vector)
{
	char *temp_contain = NULL;
	assert(NULL != vector);	
	
	--vector->size;
		
	if ((0.25 * vector->capacity) == vector->size)
	{
		vector->capacity /= 2;
		
		temp_contain = (char*)realloc((void*)vector->base_ptr, vector->element_size * vector->capacity);
		
		if (NULL == temp_contain)
		{
			return (FAIL);
		}
	
	}
	
	vector->base_ptr = temp_contain;
	
	return (SUCCESS);	
}

/*Gets the value of the element in the given index*/
void *DVectorGetAccessToElement(const dvector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert(vector->size >= index);
	
	return ((void*)(vector->base_ptr + (vector->element_size * index)));
}

/*Increases the vector capacity*/
int DVectorReserve(dvector_t *vector, size_t new_capacity)
{
	char *temp_contain = NULL;
	assert(NULL != vector);
	
	if (vector->capacity >= new_capacity)
	{
		return (FAIL);
	} 
	
	temp_contain = (char*)realloc((void*)vector->base_ptr, new_capacity * vector->element_size);
	
	if (NULL == temp_contain)
	{
		return (FAIL);
	}
	
	vector->base_ptr = temp_contain;
	vector->capacity = new_capacity;
	
	return (SUCCESS);
}

/*Shrinks the vector capacity*/
int DVectorShrink(dvector_t *vector)
{
	char *temp_contain = NULL;
	assert(NULL != vector);
	
	temp_contain = (char*)realloc((void*)vector->base_ptr, (vector->element_size * vector->size * 1.25));
	
	if (NULL == vector->base_ptr)
	{
		return FAIL;
	}
	
	vector->base_ptr = temp_contain;
	vector->capacity = vector->size * 1.25;
	
	return (SUCCESS);
}

/*Reveales the vector size*/
size_t DVectorSize(const dvector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->size);
}

/*Reveales the vector capacity*/
size_t DVectorCapacity(const dvector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->capacity);
}
