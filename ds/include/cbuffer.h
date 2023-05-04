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
		- count : The number of bytes to read. ד
Return value: If at least one byte was written return the number of bytes. If it fails return -1.
Time complexity;
Space complexity;
*/
ssize_t CBuffRead(cbuff_t *cbuffer, void *dest, size_t count);

/*==================================================================
Description:
Args:	
		-
		-
Return value: If at least one byte was read return the number of bytes. If it fails return -1.
Time complexity;
Space complexity;
*/
ssize_t CBuffWrite(cbuff_t *cbuffer, const void *src, size_t count);

/*==================================================================
Description:
Args:	
		-
		-
Return value:
Time complexity;
Space complexity;
*/
size_t CBuffFreeSpace(const cbuff_t *cbuffer);

/*==================================================================
Description:
Args:	
		-
		-
Return value:
Time complexity;
Space complexity;
*/
size_t CBuffCapacity(const cbuff_t *cbuffer);

/*==================================================================
Description:
Args:	
		-
		-
Return value:
Time complexity;
Space complexity;
*/
int CBuffIsEmpty(const cbuff_t *cbuffer);


#endif /*__CBUFFER_H__*/
