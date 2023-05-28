/*
Dev: BarSH
Rev: EtaiSH
Status: Test impl.
Date: 24.5.23
*/

#ifndef __ILRD_VSA__
#define __ILRD_VSA__

#include <stddef.h> /* size_t */
/* Read about deadbeef */
typedef struct BlockHeader vsa_t;
/*
typedef struct blk_hdr
{
	long size_of_chunk;
	
	#ifndef NDEBUG
	long magic_num;
	#endif NDEBUG
	
}blk_hdr_t;*/


/*============================================================================*/
/*
Name: VSAInit
Description: Initializes a Variable Size Allocator (VSA) using a pre-allocated memory block.
Arguments:
	- allocated_memory: Pointer to the memory block allocated for
	  the VSA
	- allocated_size: Size of the allocated memory block
Return: Pointer to the initialized VSA structure
	    (Current largest chunck)
Time complexity: O(1)
Space complexity: O(1)
*/
vsa_t *VSAInit(void *allocated_memory, size_t allocated_size);

/*============================================================================*/
/*
Name: VSAAlloc
Description: Allocates a block from the Variable Size Allocator (VSA).
Arguments:
	- vsa: A valid pointer to the VSA structure
	- num_of_bytes: Size of the block to be allocated
Return: Pointer to the allocated block or NULL if allocation fails
Time complexity: O(n)
Space complexity: O(1)
*/
void *VSAAlloc(vsa_t *vsa, size_t num_of_bytes);

/*============================================================================*/
/*
Name: VSAFree
Description: Frees a previously allocated block in the memory pool.
	- block_to_free: A valid pointer to the block to be freed
Return: void
Time complexity: O(1)
Space complexity: O(1)
*/
void VSAFree(void *block_to_free);

/*============================================================================*/
/*
Name: VSAGetLargestChunkAvailable
Description: Retrieves the size of the largest free chunk in the memory
			 pool.
Arguments:
	- vsa: A valid pointer to the VSA structure
Return: Size of the largest free chunk
Time complexity: O(n)
Space complexity: O(1)
*/
size_t VSAGetLargestChunkAvailable(vsa_t *vsa);


#endif /* __ILRD_VSA__ */

