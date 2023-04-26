/*
Dev: BarSH
Rev: EtaiSH
Date: 26.4.23
Status: Fixed
*/

#ifndef __DVECTOR_H__
#define __DVECTOR_H__

#include <stddef.h> /* size_t, NULL */

typedef struct DVector dvector_t;

/***********************************************************************/
/*
Description: Creates a dynamic vector.
Arguments:
	*element_size - The size of the elements stored in the vector, must be above 0.
	*capacity - The maximum amount of elements the vector can contain, must be above 0. 
Return:
	A dynamic vector of type dvector_t
Time complexity:	O(1)
Space complexity:	O(n*m)
*/
dvector_t *DVectorCreate(size_t element_size, size_t capacity);

/***********************************************************************/
/*
Description: Eliminates the vector.
Arguments:
	*dvector_t - A valid dynamic vector pointer.
Return:
	Returns nothing. 
Time complexity:	O(1)
Space complexity:	O(1)
*/
void DVectorDestroy(dvector_t *vector);

/***********************************************************************/
/*
Description: Adds an element into the vector.
Arguments:
	*dvector_t - A valid dynamic vector pointer.
	*element - A const valid void pointer of an element to add.
Return: 
	0 in case of successful push; -1 in case of failure.
Time complexity:	O(1)
Space complexity:	O(1)
*/
int DVectorPushBack(dvector_t *vector,const void *element);

/***********************************************************************/
/*
Description: Remove last element from vector. Shrinks memory by 2 if 
			capacity is at/under 25%.
Arguments:
	*dvector_t - A valid dynamic vector pointer.
Return: 
	0 in case of successful pop; -1 in case of failure.
Time complexity:	O(1)
Space complexity:	O(1)

*/
int DVectorPopBack(dvector_t *vector);

/***********************************************************************/
/*
Description: Retrieve a value in the vector by a given index.
Arguments:
	*dvector_t - A const valid dynamic vector pointer.
	*index - A valid index to access, index must be smaller than or equal to capacity.
Return:
	Returns a void pointer of the value.
Time complexity:	O(1)
Space complexity:	O(1)
*/
void *DVectorGetAccessToElement(const dvector_t *vector, size_t index);

/***********************************************************************/
/*
Description: Get the amounts of elements stored in the vector.
Arguments:
	*dvector_t - A const valid dynamic vector pointer.
Return:
	Returns the amount of elements int the vector as a size_t type. 
Time complexity:	O(1)
Space complexity:	O(1)
*/
size_t DVectorSize(const dvector_t *vector);

/***********************************************************************/
/*
Description: Get the capacity of the vector.
Arguments:
	*dvector_t - A const valid dynamic vector pointer.
Return:
	Returns the maximum amounts of elements in the vector as a size_t type. 
Time complexity:	O(1)
Space complexity:	O(1)
*/
size_t DVectorCapacity(const dvector_t *vector);

/***********************************************************************/
/*
Description: Increase the capacity of the vector.
Arguments:
	*dvector_t - A valid dynamic vector pointer.
Return:
	Returns the maximum amounts of elements in the vector as a size_t type. 
Time complexity:	O(1)
Space complexity:	O(n)
*/
int DVectorReserve(dvector_t *vector, size_t new_capacity);

/***********************************************************************/
/*
Description: Change available memory to 125% of the current size.
Arguments:
	*dvector_t - A val__D_VECTOR_H__id dynamic vector pointer.
Return:
	0 in case of successful pop; -1 in case of failure.
Time complexity:	O(1)
Space complexity:	O(1)
*/
int DVectorShrink(dvector_t *vector);


#endif /*__DVECTOR_H__*/

