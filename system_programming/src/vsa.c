/*
Dev: BarSH
Rev: EtaiSH
Status: Test impl.
Date: 24.5.23
*/

#include <assert.h>/*assert*/
#include <stdlib.h>/*size_t*/

#include "vsa.h"

static void *DefragBlock(vsa_t *vsa, long num_of_bytes);
static long Absolute(long num_of_bytes);
static size_t AlignBlock(size_t block_size);
static char *GetNextVSA(char *current);
static long GetVSAChunk(vsa_t *current);
static void SetVSAChunk(vsa_t *current, long num_of_bytes);

enum BOOL
{
	FALSE = 0, 
	TRUE = 1
};

typedef struct BlockHeader
{
	long size_of_chunk;
	
	#ifndef NDEBUG
	long magic_num;
	#endif /*NDEBUG*/
	
}blk_hdr_t;


#define VSA_SIZE (sizeof(vsa_t))
#define DEAD_BEEF (0xDEADBEEF)
#define WORD (sizeof(size_t))
#define END (0)

/*Initiates the managing strcut*/
vsa_t *VSAInit(void *allocated_memory, size_t allocated_size)
{
	vsa_t *head = NULL;
	vsa_t *tail = NULL;

	assert(NULL != allocated_memory);
	assert(0 < allocated_size);
	
	allocated_size = AlignBlock(allocated_size);
	
	head = (vsa_t *)allocated_memory;
	SetVSAChunk(head, (allocated_size - VSA_SIZE));
	
	tail = (vsa_t *)GetNextVSA((char *)head);
	SetVSAChunk(tail, END);
	
	#ifndef NDEBUG
	head->magic_num = DEAD_BEEF;
	tail->magic_num = DEAD_BEEF;
	#endif
	
	return (head);
}

/*Allocates a new block*/
void *VSAAlloc(vsa_t *vsa, size_t num_of_bytes)
{	
	vsa_t *current_vsa = NULL;
	vsa_t *new_vsa = NULL;
	long save_size = 0;
	char *new_block = NULL;
	
	assert(NULL != vsa);
	assert(0 != num_of_bytes);
	
	num_of_bytes = AlignBlock(num_of_bytes);
	
	current_vsa = (vsa_t *)DefragBlock(vsa, (long)num_of_bytes);
	if (NULL == current_vsa)
	{
		return (NULL);
	}
	
	if (((long)(num_of_bytes + VSA_SIZE)) > GetVSAChunk(current_vsa))
	{
		new_block = (char *)current_vsa;
		return (new_block);
	}
	/*We need to save the previous values of the buggest free chunk to 
	  update the new vsa*/
	new_vsa = current_vsa;
	save_size = GetVSAChunk(current_vsa) - VSA_SIZE - num_of_bytes;
	
	new_vsa = (vsa_t *)((char *)new_vsa + VSA_SIZE + num_of_bytes);
	SetVSAChunk(new_vsa, save_size);
	SetVSAChunk(current_vsa, -(num_of_bytes + VSA_SIZE));
	
	
	#ifndef NDEBUG
	current_vsa->magic_num = DEAD_BEEF;
	new_vsa->magic_num = DEAD_BEEF;
	#endif 
	
	new_block = (char *)current_vsa + VSA_SIZE;
	
	
	return (new_block);
}

/*Free's a current block*/
void VSAFree(void *block_to_free)
{
	char *runner = NULL;
	
	if (NULL == block_to_free)
	{
		return;
	}
	
	runner = (char *)block_to_free;
	
	runner -= VSA_SIZE;
	
	#ifndef NDEBUG
	assert(DEAD_BEEF == (((vsa_t *)runner)->magic_num));
	#endif
	
	SetVSAChunk(((vsa_t *)runner), -(GetVSAChunk((vsa_t *)runner)));
}

/*Get's the large chunk avialable*/
size_t VSAGetLargestChunkAvailable(vsa_t *vsa)
{
	long max = 0;
	long current = 0;
	char *runner = NULL;
	
	assert(NULL != vsa);
	
	runner = (char *)vsa;
	current = vsa->size_of_chunk;
	
	while (END != current) 
	{	
		if (current > max)
		{
			max = current;
		} 	
			
		runner = GetNextVSA(runner);
		current = GetVSAChunk((vsa_t *)runner);				
	}
	
	max = *((size_t *)DefragBlock(vsa, max));
	
	return (max);	
}

/***************************STATIC FUNCTIONS***********************************/
static size_t AlignBlock(size_t block_size)
{
	if (0 != block_size % WORD)
	{
		return (block_size += (WORD - (block_size % WORD)));
	}
	
	return (block_size);
}

static void *DefragBlock(vsa_t *vsa, long num_of_bytes)
{
	vsa_t *to_save = NULL;
	vsa_t *to_free = NULL;
	char *defrager = NULL;
	int is_positive = FALSE;
	
	assert(NULL != vsa);
	
	to_save = vsa;
	to_free = vsa;
	
	while (END != GetVSAChunk(to_free) && num_of_bytes > GetVSAChunk(to_save))
	{
		if (TRUE == is_positive)
		{
			SetVSAChunk(to_save, (GetVSAChunk(to_save) + GetVSAChunk(to_free)));
		}
		
		if (0 < GetVSAChunk(to_free) && TRUE != is_positive)
		{
			is_positive = TRUE;
			to_save = to_free;
		} 
		
		if (0 > GetVSAChunk(to_free))
		{
			is_positive = FALSE;
		}  
	
		to_free = (vsa_t *)GetNextVSA((char *)to_free);	
	}
	
	if (GetVSAChunk(to_save) >= num_of_bytes)
	{
		defrager = (char *)to_save;
	}
	
	return (defrager);
}

static long Absolute(long num_of_bytes)
{
	return ((0 < num_of_bytes) ? num_of_bytes : num_of_bytes * -1);
}

static char *GetNextVSA(char *current)
{	
	return (current + Absolute(GetVSAChunk((vsa_t *)current)));
}

static long GetVSAChunk(vsa_t *current)
{
	assert(NULL != current);
	
	return (current->size_of_chunk);
}

static void SetVSAChunk(vsa_t *current, long num_of_bytes)
{
	assert(NULL != current);
	
	current->size_of_chunk = num_of_bytes;
}


