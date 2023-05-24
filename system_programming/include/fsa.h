/*
Dev: BarSH
Rev: 
Status: Test impl.
Date: 19.5.23
*/

#ifndef __ILRD_FSA__
#define __ILRD_FSA__

#include <stddef.h> /*NULL, size_t*/

typedef struct Fsa fsa_t;
/*
struct Fsa
{
	size_t next_available;
};
*/

/*============================================================================*/
/*
Name: FSAInit
Description: 
Arguments: 
Return: 
Time complexity: O(n)
Space complexity: O(1)
*/
fsa_t *FSAInit(void *ptr_to_memory, size_t allocated_size, size_t block_size);

/*============================================================================*/
/*
Name: FSAAlloc		
Description:
Arguments: 
Return: 
Time complexity: O(1)
Space complexity: O(1)
*/
void *FSAAlloc(fsa_t *fsa);

/*============================================================================*/
/*
Name: FSAFree
Description:
Arguments: 
Return: 
Time complexity: O(1)
Space complexity: O(1)
*/
void FSAFree(fsa_t *fsa, void *block_to_free);

/*============================================================================*/
/*
Name: FSACountFree
Description:
Arguments: 
Return: 
Time complexity: O(n)
Space complexity: O(1)
*/
size_t FSACountFree(const fsa_t *fsa);

/*============================================================================*/
/*
Name: FSASuggestSize
Description: 
Arguments: 
Return: 
Time complexity: O(1)
Space complexity: O(1)
*/
size_t FSASuggestSize(size_t block_number, size_t size_of_block);

#endif /*__ILRD_FSA__*/

