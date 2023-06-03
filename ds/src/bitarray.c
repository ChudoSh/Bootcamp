/*
Dev: BarSh
Rev: Grag 
Date 19.4.23
Status: Fixed
*/

#include <stddef.h>
#include <assert.h>

#include "bitarray.h"

#define ONE (1UL)
#define ZERO (0UL)
#define TWO (2UL)
#define CHAR_SIZE (__CHAR_BIT__)
#define SIZE_ARR (sizeof(size_t) * CHAR_SIZE)
#define SIZE_LUT (256)
#define UNUSED(a) ((void)a)
#define NIBBLE (CHAR_SIZE / 2)
#define POS_TO_INDEX(pos) (pos - 1)
#define MASK_SIZE (6)

bitarr_t BitArrSetOn(bitarr_t arr, size_t pos)
{	
	assert(SIZE_ARR > pos);
	
	return (BitArrSet(arr, pos, ONE));
	/*Given arr 1 and pos 2 :0001 | (0001 << 1) -> 0001 | 0010 -> 0011*/	 
}

bitarr_t BitArrSetOff(bitarr_t arr, size_t pos)
{
	assert(SIZE_ARR > pos);
	
	return (BitArrSet(arr, pos, ZERO));
	/*Given arr 2 and pos 2 :(0010 | ~(0001 << 1)) -> (0001 | (1101)) -> 0011*/
}

bitarr_t BitArrSet(bitarr_t arr, size_t pos, int bool_val)
{	
	assert(SIZE_ARR > pos);
	assert(2 > bool_val);
	assert(-1 < bool_val);

	return ((arr  & ~(ONE << POS_TO_INDEX(pos))) | (bool_val << POS_TO_INDEX(pos)));
	/*Given arr 2, pos 2 and val 1 :(0010 | (0000 << 1)) -> (0001 | (1101)) -> 0011*/	
}

size_t BitArrGetVal(bitarr_t arr, size_t pos)
{
	assert(SIZE_ARR > pos);
	
	return (arr & (ONE << POS_TO_INDEX(pos)));
	/*Given arr 1 and pos 2 :(0010 & (0001 << 1) -> (0001 & 0010) -> 0000*/
}

bitarr_t BitArrSetAll(bitarr_t arr)
{
	return (~ZERO);
	UNUSED(arr);
	/*Sets 0 as size_t and flips it*/
}

bitarr_t BitArrResetAll(bitarr_t arr)
{
	return (!BitArrSetAll(arr));
	/* The opposite for SetAll*/
}

size_t BitArrCountOn(bitarr_t arr)
{
	size_t count = 0; 
	
	while (0 < arr)
	{	
		arr = arr & (arr - 1); /*The Kernighan Algorithm*/
		++count;	
	}
	
	return count; 		
}

size_t BitArrCountOff(bitarr_t arr)
{
	return (SIZE_ARR - BitArrCountOn(arr));
	/*Maximum amount of bits minus the counted*/
}

bitarr_t BitArrFlip(bitarr_t arr, size_t pos)
{
	return (BitArrSet(arr, pos, !(BitArrGetVal(arr, pos))));
	/*Sets the !value in the given position*/
}


bitarr_t BitArrMirror(bitarr_t arr)
{
	size_t i = 0;
	static size_t mask[MASK_SIZE] = 
	{
		0x5555555555555555,/*01010101..*/ 
		0x3333333333333333,/*011011011..*/
		0x0F0F0F0F0F0F0F0F,/*111100001111..*/
		0x00FF00FF00FF00FF,/*1111111100000000..*/
		0x0000FFFF0000FFFF,/*11111111111111110000000000000000..*/
		0x00000000FFFFFFFF /*32's 1 and 32's 0*/
	};
	
	for (i = 0; i < MASK_SIZE; ++i)
	{
		arr = ((arr & mask[i]) << (ONE << i)) | ((arr & ~(mask[i])) >> (ONE << i));
		/*The Hamming Weight Algorithm*/	
	}
	
	return (arr);		
}

bitarr_t BitArrRotateLeft(bitarr_t arr, size_t shift)
{
	assert(ZERO < shift);
	
	return ((arr << shift) | (arr >> (shift - SIZE_ARR)));
}

bitarr_t BitArrRotateRight(bitarr_t arr, size_t shift)
{
	assert(ZERO < shift);
	
	return ((arr >> shift) | (arr << (shift - SIZE_ARR)));
}

char *BitArrToString(bitarr_t arr, char *dest)
{
	int i = (SIZE_ARR);
    
    assert(NULL != dest);
    
	dest[SIZE_ARR] = '\0';
	
    while (0 <= i)
    {
    	--i;
    	dest[i] = (arr & ONE) + 48;  
        arr = arr >> 1;
    }
     
    return (dest);
}

size_t BitArrCountOnLUT(bitarr_t arr)
{
	size_t count = 0; 
	size_t i = 0;
	static size_t LUT[SIZE_LUT];
	static size_t flag = 0;
	
	if (0 == flag)
	{
		for (i = 0; SIZE_LUT > i; ++i)
		{
			LUT[i] = BitArrCountOn(i);
		}
				
		flag = 1;
	}
	
	i = 0;
	
	while (CHAR_SIZE > i)
	{
		count += LUT[(arr % CHAR_SIZE)]; 
		arr /= CHAR_SIZE;
		++i;
	}
	
	return (count);		
}
