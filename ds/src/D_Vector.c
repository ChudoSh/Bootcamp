/*
Dev: BarSH
Rev: EtaiSH
Date: 26.4.23
Status: Fixed
*/ 

#include <stdlib.h>	/*malloc, free*/
#include <string.h>	/*memcpy*/
#include <assert.h> /*assert*/

#include "D_Vector.h"

#define GROWTH_FACTOR 2
#define SHRINK 1.25
#define POP_CHECK 0.25
#define EMPTY 0

#define MULT_BY_ELEM_SIZE(x, v) (x * v->element_size)



static int DVectorResize(dvector_t *vector , size_t new_size);
 
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
	dvector_t *vector = NULL;
	
	assert(EMPTY < element_size);
	assert(EMPTY < capacity);
		
	vector = (dvector_t*)malloc(sizeof(dvector_t));
	
	if (NULL == vector)
	{
		return (NULL);
	}
	
	vector->base_ptr = (char*)(malloc(element_size * capacity));
	
	if (NULL == vector->base_ptr)
	{
		free(vector);
		vector = NULL;
		return (NULL);
	
	}
	
	vector->capacity = capacity;
	vector->size = EMPTY;
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
}

/*Adds an element to the vector*/
int DVectorPushBack(dvector_t *vector, const void *element)
{
	
	assert(NULL != vector);
	assert(NULL != element);
	
	if (vector->capacity == vector->size)
	{
		vector->capacity *= GROWTH_FACTOR;
		
		if (FAIL == DVectorResize(vector,  vector->capacity))
		{
			return (FAIL);
		}
	}
	
	if (NULL == memcpy(vector->base_ptr + (MULT_BY_ELEM_SIZE(vector->size, vector)), element, vector->element_size))
	{
		return (FAIL);
	}
		
	++(vector->size);
	
	return (SUCCESS);
}

/*Removes the top element of the vector*/
int DVectorPopBack(dvector_t *vector)
{
	assert(NULL != vector);	
	assert(EMPTY != vector->size);
	
	--(vector->size);
		
	if ((POP_CHECK * vector->capacity) == vector->size)
	{
		vector->capacity /= GROWTH_FACTOR;
		
		if (FAIL == DVectorResize(vector, vector->capacity))
		{
			return (FAIL);
		}
	}
	
	return (SUCCESS);	
}

/*Gets the value of the element in the given index*/
void *DVectorGetAccessToElement(const dvector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert(vector->capacity >= index);
	
	return ((void*)(vector->base_ptr + (MULT_BY_ELEM_SIZE(index, vector))));
}

/*Increases the vector capacity*/
int DVectorReserve(dvector_t *vector, size_t new_capacity)
{
	assert(NULL != vector);
	
	if (vector->size > new_capacity)
	{
		return (FAIL);
	} 
	
	if (FAIL == DVectorResize(vector,  new_capacity))
	{
		return (FAIL);
	}
	 
	vector->capacity = new_capacity;
	
	return (SUCCESS);
}

/*Shrinks the vector capacity*/
int DVectorShrink(dvector_t *vector)
{
	assert(NULL != vector);
	
	if (vector->capacity < vector->size * SHRINK)
	{
		return (FAIL);
	}
	
	if (FAIL == DVectorResize(vector, (vector->size * SHRINK)))
	{
		return (FAIL);
	}
	
	vector->capacity = vector->size * SHRINK;
	
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

static int DVectorResize(dvector_t *vector, size_t new_size)
{	
	char *temp = NULL;
	
	assert(NULL != vector);
	
	if (GROWTH_FACTOR == new_size)
	{
		temp = (char*)realloc((void*)vector->base_ptr, (MULT_BY_ELEM_SIZE(vector->capacity, vector)));		
	}
	
	else
	{
		temp = (char*)realloc((void*)vector->base_ptr, (MULT_BY_ELEM_SIZE(new_size, vector)));
	}
	
	vector->base_ptr = temp;
		
	return ((NULL == vector->base_ptr) ? FAIL : SUCCESS);
}
