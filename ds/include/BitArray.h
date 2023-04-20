/*
Dev: BarSh
Rev: Grag 
Date 19.4.23
Status: Fixed
*/

#ifndef __BITARRAY_H__
#define __BITARRAY_H__


typedef size_t bitarr_t;

/*
Description: Sets the bit in a given position to 1
Arguments:
	*arr - A bit array.
	*pos - A valid position between 0 and 64.
Return: 
	Bit array.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrSetOn(bitarr_t arr, size_t pos);

/*
Description: Sets the bit in a given position to 0
Arguments:
	*arr - A bit array.
	*pos - A valid position between 0 and 64.
Return: 
	Bit array.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrSetOff(bitarr_t arr, size_t pos);

/*
Description: Sets the bit in a given position to 0
Arguments:
	*arr - A bit array.
	*pos - A valid position between 0 and 64.
Return: 
	Bit array.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrSet(bitarr_t arr, size_t pos, int bool_val);

/*
Description: Returns the bit value in a given position.
Arguments:
	*arr - A bit array.
	*pos - A valid position between 0 and 64.
Return: 
	A value of 1 or 0.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
size_t BitArrGetVal(bitarr_t arr, size_t pos);

/*
Description: Sets the array to 1.
Arguments:
	*arr - A bit array.
Return: 
	A bit array where all the bits are 1.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrSetAll(bitarr_t arr);

/*
Description: Sets the array to 0.
Arguments:
	*arr - A bit array.
Return: 
	A bit array where all the bits are 0.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrResetAll(bitarr_t arr);

/*
Description: Counts the number of bits set to 1 in a given array.
Arguments:
	*arr - A bit array.
Return: 
	A size_t with the number of bits set to 1.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
size_t BitArrCountOn(bitarr_t arr);

/*
Description: Counts the number of bits set to 0 in a given array.
Arguments:
	*arr - A bit array.
Return: 
	A size_t with the number of bits set to 0.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
size_t BitArrCountOff(bitarr_t arr);

/*
Description: Counts the number of bits set to 1 in a given array using a LUT.
Arguments:
	*arr - A bit array.
Return: 
	A size_t with the number of bits set to 1.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
size_t BitArrCountOnLUT(bitarr_t arr);

/*
Description: Turns the bit in given position into its opposite value.
Arguments:
	*arr - A bit array.
	*pos - A valid position between 0 and 64.
Return: A bit array with the given position flipped.
Complexity: Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrFlip(bitarr_t arr, size_t pos);

/*
Description: Mirrors the bit array given.
Arguments:
	*arr - A bit array.
Return: 
	A bit array with the given position flipped.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrMirror(bitarr_t arr);

/*
Description: Rotates the bit array to the left by a given number.
Arguments:
	*arr - A bit array.
	*shift - Amount of rotations.
Return: 
	The bit array rotated to the left.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrRotateLeft(bitarr_t arr, size_t shift);

/*
Description: Rotates the bit array to the right by a given number.
Arguments:
	*arr - A bit array.
	*shift - Amount of rotations.
Return: 
	The bit array rotated to the right.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
bitarr_t BitArrRotateRight(bitarr_t arr, size_t shift);


/*
Description: Converts the array into a string.
Arguments:
	*dest - A valid string pointer equal or bigger than 64.
	*arr - A bit array.
Return: 
	The pointer to the string.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
char *BitArrToString(bitarr_t arr, char *dest);

/*
Description: Mirrors the bit array using a LUT.
Arguments:
	*arr - A bit array.
Return: 
	The mirrored bit array.
Complexity: 
	Time - 0(1) / Space - 0(1).
*/
size_t BitArrMirrorLUT(bitarr_t arr);

#endif/*__BITARRAY_H__*/
