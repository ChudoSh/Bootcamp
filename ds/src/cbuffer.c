/*
Dev: BarSH
Rev: EtaiSH
Status: Approved
Date: 3.5.23
*/

#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc*/

#include "cbuffer.h"

#define BUFF_START_INDEX(buff) (buff->buffer[(buff->start % buff->capacity)])
#define BUFF_END_INDEX(buff) (buff->buffer[((buff->end + 1) % buff->capacity)])


enum MACRO
{
	FAIL = -1,
	IS_EMPTY = -1,
	ZERO = 0,
	ONE = 1
};


struct CBuff
{
	size_t capacity;
	ssize_t start;
	ssize_t end;
	char buffer[ONE];
};

/*Creates a circular buffer*/
cbuff_t *CBuffCreate(size_t capacity)
{
	cbuff_t *cbuff = NULL; 
	
	assert(ZERO != capacity); 
	
	cbuff = (cbuff_t *)malloc(capacity + sizeof(cbuff_t)); 
	
	if (NULL == cbuff)
	{
		return (NULL);
	}
	
	cbuff->start = ZERO; 
	cbuff->end = IS_EMPTY;
	cbuff->capacity = capacity;
	
	return (cbuff);
}

/*Eliminates a circular buffer*/
void CBuffDestroy(cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	free(cbuff);
}

/*Reads from the circular buffer*/
ssize_t CBuffRead(cbuff_t *cbuff, void *dest, size_t count)
{
	size_t temp = count;
	char *runner = NULL; 
	
	assert(NULL != cbuff);
	assert(NULL != dest);
	
	runner = (char *)dest;
	
	if (TRUE == CBuffIsEmpty(cbuff))
	{
		return (FAIL);
	} 
	
	while (ZERO < count)
	{
		*((char *)runner) = BUFF_START_INDEX(cbuff);
		
		--(count);	
		
		if (cbuff->end == cbuff->start)
		{
			cbuff->end = IS_EMPTY;
			cbuff->start = ZERO;
			
			return (temp - count);
		}
		
		++(cbuff->start);
		++(runner);
	}
	
	return (temp - count);	
}
	


/*Writes to the circular buffer*/
ssize_t CBuffWrite(cbuff_t *cbuff, const void *src, size_t count)
{
	size_t temp = count;
	char *runner = NULL; 
	
	assert(NULL != cbuff);
	assert(NULL != src);
	
	runner = (char *)src;
	
	if (ZERO == CBuffFreeSpace(cbuff))
	{
		return (FAIL);
	} 

	if (count > CBuffFreeSpace(cbuff))
	{
		count = CBuffFreeSpace(cbuff);
		temp = count;
	} 
	
	while (ZERO < count)
	{
		 BUFF_END_INDEX(cbuff) = *((char *)runner);
		 
		--(count);
		++(cbuff->end);
		++(runner);
	}
	
	return (temp - count);
}

/*Gets the capacity of the circular buffer*/
size_t CBuffCapacity(const cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (cbuff->capacity);
}

/*Checks if the circular buffer is empty*/
int CBuffIsEmpty(const cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	return (IS_EMPTY == cbuff->end);
}

size_t CBuffFreeSpace(const cbuff_t *cbuff)
{
	assert(NULL != cbuff);
	
	if (CBuffIsEmpty(cbuff))
	{
		return (CBuffCapacity(cbuff));
	}
	
	if (cbuff->start <= cbuff->end)
	{
		return (cbuff->capacity - ((cbuff->end + ONE) - cbuff->start));
	}
	 
	return (cbuff->start - cbuff->end);
}
