/*
Dev: BarSH
Rev: MariaP
Status: Approved
Date: 19.4.23
*/

#ifndef __ITOAATOI_H__
#define __ITOAATOI_H__

enum MACROS
{
	BINARY_BASE = 2,
    DECIMAL_BASE = 10,
    VAL_OF_ZERO = 48,
    MAX_BASE = 36    
};   

/*
Description: Converts a given ineger into n a string, decimal base.
arguments:
	*n 	 - The number that needs to be converted.
    *buffer - A valid char pointer that will store the the retrun value.
    *base - A number between 2 and 36 on which the base conversion is determined. 
   	return: Retruns the string pointer.
*/
char *Itoa(int n, char *buffer, int base);

/*
Description: Converts a given string into an integer, decimal base.
arguments:
    *buffer - A valid char pointer to be converted.
return: Returns the integer pointer.
*/
int Atoi(const char *buffer);




#endif /*__ITOAATOI_H__*/
