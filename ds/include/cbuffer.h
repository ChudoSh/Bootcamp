/*
Dev: BarSH
Rev: EtaiSH
Status: Approved
Date: 3.5.23
*/

#ifndef __CBUFFER_H__
#define __CBUFFER_H__

#include <stdlib.h>
#include <aio.h>

typedef struct CBuff cbuff_t;

/*
	buffer should not overwrite!
*/

/*==================================================================
Description: Creates a circular buffer
Arguments:	
		- Capacity : a valid size of capacity, must be bigger than 0.
Return value:
	A valid pointer to a circular buffer.	
Time complexity: O(1)
Space complexity: O(n)
*/
cbuff_t *CBuffCreate(size_t capacity);

/*==================================================================
Description: Destorys a circular buffer
Arguments:	
		- buffer : a valid pointer to circular buffer.
Return value:
	None.	
Time complexity: O(1)
Space complexity: O(1)
*/
void CBuffDestroy(cbuff_t *cbuffer);

/*==================================================================
Description: Reads from the buffer into a destination. 
Args:	
		- cbuffer : A valid buffer pointer. 
		- dest : A valid destination to receive the data.
		- count : The number of bytes to read.
Return value: If at least one byte was written return the number of bytes. If it fails return -1.
Time complexity: O(n)
Space complexity: O(1)
*/
ssize_t CBuffRead(cbuff_t *cbuffer, void *dest, size_t count);

/*==================================================================
Description: Writes the in a source variable into the buffer.
Args:	
		- cbuffer : A valid circular buffer pointer. 
		- src : A valid pointer to the source data. 
Return value: If at least one byte was read return the number of bytes. If it fails return -1.
Time complexity: O(n)
Space complexity: O(1)
*/
ssize_t CBuffWrite(cbuff_t *cbuffer, const void *src, size_t count);

/*==================================================================
Description: Checks the amount of avaiable space in the buffer. 
Args:	
		- cbuffer : A const valid circular buffer pointer.
Return value:
	The amount of free space in the buffer (size_t);
Time complexit: O(1)
Space complexity: O(1)
*/
size_t CBuffFreeSpace(const cbuff_t *cbuffer);

/*==================================================================
Description: Shows the capacity of the buffer. 
Args:	
		- cbuffer : A const valid circular buffer pointer.
Return value:
	The capacity of the buffer. 
Time complexity;
Space complexity;
*/
size_t CBuffCapacity(const cbuff_t *cbuffer);

/*==================================================================
Description: Checks whether or not the buffer is empty. 
Args:	
		- cbuffer : A const valid circular buffer pointer.
Return value:
	1 if empty, 0 otherwise. 
Time complexity: O(1)
Space complexity: O(1)
*/
int CBuffIsEmpty(const cbuff_t *cbuffer);


#endif /*__CBUFFER_H__*/
