/*
Dev: BarSH
Rev: 
Status: Test impl.
Date: 23.5.23
*/

#include <assert.h> /*assert*/

#include "fsa.h"

#define WORD (sizeof(size_t))
#define DRY_POOL (0)

static size_t AlignBlock(size_t block_size);

struct Fsa
{
	size_t next_available;
};


fsa_t *FSAInit(void *ptr_to_memory, size_t allocated_size, size_t block_size)
{
	size_t i = 1; 
	unsigned char *runner = NULL;
	fsa_t *fsa = NULL;
	
	assert(NULL != ptr_to_memory);
	assert(0 == ((size_t)ptr_to_memory % WORD));
	assert(0 != allocated_size);
	assert(0 != block_size);
	
	block_size = AlignBlock(block_size);
	
	runner = (unsigned char *)ptr_to_memory;
	fsa = (fsa_t *)runner;
	fsa->next_available = WORD; 
	runner += WORD;
	
	while (block_size < (allocated_size - WORD))
	{	
		*(size_t *)runner = i * block_size + WORD;
		runner += block_size;
		allocated_size -= block_size;
		++(i);
	}
	
	*(size_t *)runner = DRY_POOL;
	
	return (fsa);
}

void *FSAAlloc(fsa_t *fsa)
{
	void *block = NULL; 
	
	assert(NULL != fsa);
	
	if (DRY_POOL == fsa->next_avaiable)
	{
		return (NULL);
	}
	
	block = ((char *)fsa + fsa->next_available);
	
	fsa->next_available = *((size_t *)block);
	
	return (block);	
}

void FSAFree(fsa_t *fsa, void *block_to_free)
{ 	
	assert(NULL != fsa);
	
	if(NULL == block_to_free)
	{
		return;
	}
	
	*(size_t *)block_to_free = fsa->next_available;
		
	fsa->next_available = (char *)block_to_free - (char *)fsa;	
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t count = 0;
	size_t offset = 0;
	char *runner = NULL;
	
	assert(NULL != fsa);
	
	runner = (char *)fsa;
	offset = fsa->next_available;
	
	while (DRY_POOL != offset)
	{	
		runner = (char *)fsa + offset;
		offset = *(size_t *)runner;
		++(count);		
	}
	
	return (count);
}

size_t FSASuggestSize(size_t block_number, size_t size_of_block)
{
	assert(0 != block_number);
	assert(0 != size_of_block);
	
	return (block_number * size_of_block + WORD);
}

/***********************STATIC FUNCTIONS***************************************/
static size_t AlignBlock(size_t block_size)
{
	if (0 != block_size % WORD)
	{
		return (block_size += (WORD - (block_size % WORD)));
	}
	
	return (block_size);
}
