/*
Dev: BarSh
Rev: Grag 
Date 19.4.23
Status: Fixed
*/

#include <stdio.h> /*printf*/

#include "bitarray.h"

int main()
{
	bitarr_t test = 130;
	char str[65];
	
	if (131 == BitArrSetOn(test, 1))
	{
		printf("1.Success for BitArrSetOn\n");
	}
	else
	{
		printf("1.Fail for BitArrSetOn\n");
	}
	
	if (2 == BitArrSetOff(test, 8))
	{
		printf("2.Success for BitArrSetOff\n");
	}
	else
	{
		printf("2.Fail for BitArrSetOff\n");
	}
	
	if (2 == BitArrSet(test, 8, 0))
	{
		printf("3.Success for BitArrSet\n");
	}
	else
	{
		printf("3.Fail for BitArrSet\n");
	}
	
	if (128 == BitArrGetVal(test, 8))
	{
		printf("4.Success for BitArrGetVal\n");
	}
	else
	{
		printf("4.Fail for BitArrGetVal\n");
	}
	
	if (0xFFFFFFFFFFFFFFFF == BitArrSetAll(test))
	{
		printf("5.Success for BitArrSetAll\n");
	}
	else
	{
		printf("5.Fail for BitArrSetAll\n");
	}
	
	if (0 == BitArrResetAll(test))
	{
		printf("6.Success for BitArrResetAll\n");
	}
	else
	{
		printf("6.Fail for BitArrResetAll\n");
	}
	
	if (2 == BitArrCountOn(test))
	{
		printf("7.Success for BitArrCountOn\n");
	}
	else
	{
		printf("7.Fail for BitArrCountOn\n");
	}
	
	if (62 == BitArrCountOff(test))
	{
		printf("8.Success for BitArrCountOff\n");
	}
	else
	{
		printf("8.Fail for BitArrCountOff\n");
	}
	
	if (2 == BitArrFlip(test, 8))
	{
		printf("9.Success for BitArrFlip\n");
	}
	
	else
	{
		printf("9.Fail for BitArrFlip\n");
	}
	
	if (0x8000000000000000 == BitArrMirror(1))
	{
		printf("10.Success for BitArrMirror(includes LUT)\n");
	}
	else
	{
		printf("10.Fail for BitArrMirror\n");
	}
	
	if (test == BitArrRotateLeft(test, 64))
	{
		printf("11.Success for BitArrRotateLeft\n");
	}
	else
	{
		printf("11.Fail for BitArrRotateLeft\n");
	}
	
	if (test == BitArrRotateRight(test, 64))
	{
		printf("12.Success for BitArrRotateRight\n");
	}
	else
	{
		printf("12.Fail for BitArrRotateRight\n");
	}
	
	
	printf("13.String for 1 should be 63 0's and 1:\n%s\n", BitArrToString((size_t)1, str));	
	
	if (2 == BitArrCountOnLUT(test))
	{
		printf("14.Success for BitArrCountOnLUT\n");
	}
	else
	{
		printf("14.Fail for BitArrCountOnLUT\n");
	}
	
	return 0;	
}



