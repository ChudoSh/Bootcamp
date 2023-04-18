#include <stddef.h>
#include <assert.h>

#include "../include/BitArray.h"

bitarr_t BitArrSetOn(bitarr_t arr, size_t pos)
{	
	assert(SIZE_ARR > pos);
	return (arr | TRUE << (pos - 1));
	/*Given arr 1 and pos 2 :0001 | (0001 << 1) -> 0001 | 0010 -> 0011*/	 
}

bitarr_t BitArrSetOff(bitarr_t arr, size_t pos)
{
	assert(SIZE_ARR > pos);
	return arr & ~(TRUE << (pos - 1));
	/*Given arr 2 and pos 2 :(0010 | ~(0001 << 1)) -> (0001 | (1101)) -> 0011*/
}

bitarr_t BitArrSet(bitarr_t arr, size_t pos, int bool_val)
{	
	assert(SIZE_ARR > pos);
	assert(FALSE =< bool_val && TRUE >= bool_val);
	
	
	return ((TRUE == bool_val) ? BitArrSetOn(arr, pos) : BitArrSetOff(arr, pos));
	/*Given arr 2 and pos 2 :(0010 | ~(0001 << 1)) -> (0001 | (1101)) -> 0011*/	
}

size_t BitArrGetVal(bitarr_t arr, size_t pos)
{
	assert(SIZE_ARR > pos);
	return (arr & (TRUE << (pos - 1)));
	/*Given arr 1 and pos 2 :(0010 & (0001 << 1) -> (0001 & 0010) -> 0000*/
}

bitarr_t BitArrSetAll(bitarr_t arr)
{
	UNUSED(arr);
	return (~((size_t)FALSE));
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
		arr = arr & (arr -1); /*The Kernighan Algorithm*/
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
	static size_t shift[6] = 
	{
		0x5555555555555555,/*01010101..*/ 
		0x3333333333333333,/*011011011..*/
		0x0F0F0F0F0F0F0F0F,/*111100001111..*/
		0x00FF00FF00FF00FF,/*1111111100000000..*/
		0x0000FFFF0000FFFF,/*11111111111111110000000000000000..*/
		0x00000000FFFFFFFF /*32's 1 and 32's 0*/
	};
	
	for (i = 0; i < 6; ++i)
	{
		arr = ((arr & shift[i]) << (1 << i)) | ((arr & ~(shift[i])) >> (1 << i));
		/*The Hamming Weight Algorithm*/	
	}
	return (arr);		
}

bitarr_t BitArrRotateLeft(bitarr_t arr, size_t shift)
{
	assert(FALSE < shift);
	
	return ((arr << shift) | (arr >> (shift - SIZE_ARR)));
}

bitarr_t BitArrRotateRight(bitarr_t arr, size_t shift)
{
	assert(FALSE < shift);
	
	return ((arr >> shift) | (arr << (shift - SIZE_ARR)));
}

char *BitArrToString(bitarr_t arr, char *dest)
{
	size_t i = 0;
	size_t ch = 0;
    
    assert(NULL != dest);
    
    for(i = 63; 0 < i; --i)
    {
        ch = arr % 2; 
    	dest[i] = '0' + ch;  
        arr = arr >> 1;
    }
    
    if (0 != (arr % 2))
    {
		dest[0] = '1';    
    } 
	else
	{
    	dest[0] = '0';
	}
	
	dest[SIZE_ARR] = '\0';
     
    return (dest);
}

size_t BitArrCountOnLUT(bitarr_t arr)
{
	size_t count = 0; 
	size_t i = 0;
	static size_t LUT[SIZE_ARR];
	static size_t flag = 0;
	
	
	if (FALSE == flag)
	{
		for (i = 0;SIZE_ARR > i; ++i)
		{
			LUT[i] = BitArrCountOn(i);
		}
		
		flag = TRUE;
	}
	
	while (FALSE != arr)
	{
		count += LUT[(arr % SIZE_ARR)]; 
		arr /= SIZE_ARR;
	}
	
	return (count);		
}


static unsigned char ByteMirrors_LP(unsigned char n)
{
    unsigned int output = 0;	
	unsigned int temp = 0; 
	size_t i = 0;
	
	for(i = 0; i < 8; ++i)
	{
		output = output << 1; 
		temp = n & 1; 
		output = output | temp;
		n = n >> 1;
	}
	
	return (output); 	
	
}

size_t BitArrMirrorLUT(bitarr_t arr)
{ 
	size_t i = 0;
	size_t output = 0;
	static size_t LUT[SIZE_LUT];
	static size_t flag = 0; 
	
	if (FALSE == flag)
	{
		for (i = 0;(SIZE_LUT) > i; ++i)
		{
			LUT[i] = ByteMirrors_LP(i);
		}
		
		flag = TRUE;
	}
	
	i = 0;
	
	while (8 > i)
	{
		*((unsigned char*)&output + i) = LUT[*((unsigned char*)&arr + (7 - i))];
		/*We set the first BYTE in of output by the address of the last byte of
		arr*/  
		++i;
	}
	
	return (output);		
}

