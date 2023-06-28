#include <assert.h> /* assert */
#include <stddef.h> /*size_t*/


#include "bitarray.h"

#define NIBBLE (4)
#define CRUMB (2)
#define BITS_IN_ARR (64)
#define UNUSED(x) ((void)(x))
#define MAX_64_BIT_NUM (0xffffffffffffffff)
#define BIT_64_SET (0x8000000000000000)
#define TRUE (1)
#define FALSE (0)

bitarr_t BitArrSetOn(bitarr_t arr, size_t pos)
{	
	assert((BITS_IN_ARR - 1) >= pos);
	
	return (arr | (((bitarr_t)1 << pos)));
}

bitarr_t BitArrSetOff(bitarr_t arr, size_t pos)
{
	bitarr_t n = 1;
	assert((BITS_IN_ARR - 1) >= pos);
	
	n <<= pos;
	arr &= ~n;
	
	return (arr);
}

bitarr_t BitArrSet(bitarr_t arr, size_t pos, int bool_val)
{
	assert((BITS_IN_ARR - 1) >= pos);
	assert(0 == bool_val || 1 == bool_val);
	
	if(!bool_val)
	{
		return (BitArrSetOff(arr, pos));
	}
	else
	{
		return (BitArrSetOn(arr, pos));
	}
}

size_t BitArrGetVal(bitarr_t arr, size_t pos)
{
	bitarr_t n = 1;
	assert((BITS_IN_ARR - 1) >= pos);
	
	n <<= pos;
	
	return ((arr | n) == arr);
}

bitarr_t BitArrSetAll(bitarr_t arr)
{
	UNUSED(arr);
	return (MAX_64_BIT_NUM);
}

bitarr_t BitArrResetAll(bitarr_t arr)
{
	UNUSED(arr);
	return (0);
}

size_t BitArrCountOn(bitarr_t arr)
{
	size_t counter = 0;

	while (arr) 
	{
		arr = arr & (arr - 1);
		++counter;
	}
	
	return (counter); 
}

size_t BitArrCountOff(bitarr_t arr)
{
	return (BITS_IN_ARR - BitArrCountOn(arr));
}

bitarr_t BitArrFlip(bitarr_t arr, size_t pos)
{
	bitarr_t n = 1;
	assert((BITS_IN_ARR - 1) >= pos);
	
	n <<= pos;
	
	return (arr ^ n);
}

bitarr_t BitArrMirror(bitarr_t arr)
{
	arr = (arr >> 32) | (arr << 32);
	arr = ((arr >> 16) & 0x0000ffff0000ffff) | ((arr & 0x0000ffff0000ffff) << 16);
	arr = ((arr >> 8) & 0x00ff00ff00ff00ff) | ((arr & 0x00ff00ff00ff00ff) << 8);
	arr = ((arr >> 4) & 0x0f0f0f0f0f0f0f0f) | ((arr & 0x0f0f0f0f0f0f0f0f) << 4);
	arr = ((arr >> 2) & 0x3333333333333333) | ((arr & 0x3333333333333333) << 2);
	arr = ((arr >> 1) & 0x5555555555555555) | ((arr & 0x5555555555555555) << 1);

	return (arr);
}

bitarr_t BitArrRotateLeft(bitarr_t arr, size_t shift)
{
	shift %= BITS_IN_ARR;
	
	while(shift)
	{
		if(BitArrGetVal(arr, (BITS_IN_ARR - 1)))
		{
			arr <<= 1;
			arr += 1;
		}
		else
		{
			arr <<= 1;
		}
		--shift;
	}
	
	return (arr);
}

bitarr_t BitArrRotateRight(bitarr_t arr, size_t shift)
{	
	shift %= BITS_IN_ARR;
	
	while(shift)
	{
		if(BitArrGetVal(arr, 0))
		{
			arr >>= 1;
			arr += BIT_64_SET;
		}
		else
		{
			arr >>=1;
		}
		--shift;
	}
	
	return (arr);
}

char *BitArrToString(bitarr_t arr, char *dest)
{
	size_t i = 0;
	
	assert(NULL != dest);
	
	for(i = 1; i <= BITS_IN_ARR; ++i)
	{
		if(BitArrGetVal(arr, i))
		{
			*dest = '1';
		}
		else
		{
			*dest = '0';
		}
		++dest;
	}
	
	return (dest);
}

bitarr_t BitArrMirrorLUT(bitarr_t arr)
{
	bitarr_t mod_arr = 0;
	bitarr_t temp = 0;
	static bitarr_t LUT[BITS_IN_ARR] = {0};
	static int is_LUT_init = 0;
	size_t i = 0;
	
	if(FALSE == is_LUT_init)
	{
		for(i = 0; BITS_IN_ARR > i; ++i)
		{
			LUT[i] = BitArrSetOn(temp, (BITS_IN_ARR - 1 - i));
			temp = 0;
		}
		
		is_LUT_init = TRUE;
	}
	
	i = 0;
	
	while(arr)
	{
		if(BitArrGetVal(arr, 0))
		{
			mod_arr |= LUT[i];
		}
		++i;
		arr >>= 1;
	}
	
	return (mod_arr);
}

size_t BitArrCountOnLUT(bitarr_t arr)
{
	int counter = 0;
	static int set_bits_LUT[NIBBLE + 1] = {0, 1, 1, 2, 1};
	
	while(arr)
	{
		counter += set_bits_LUT[(arr % NIBBLE)];
		arr /= NIBBLE;
	}

	return (counter); 
}


