/*
Dev: BarSH
Rev: MariaP
Status: Approved
Date: 19.4.23
*/

#include <stdio.h>/*size_t, sprintf*/
#include <assert.h>/*assert*/
#include <ctype.h>/*isdigit*/

#include "ItoaAtoi.h"

static void ReverseString(char *dest, size_t size);

int Atoi(const char *buffer)
{
    int flag = 1; 
    int result = 0;

    assert(NULL != buffer);
	   
    while (' ' == *buffer && '\0' != *buffer)
    {
		++buffer;
    }
   
	if ('-' == *buffer)
	{
		++buffer;
	    flag = -1;
    } 
	 		
    while (isdigit(*buffer))
    {
		result *= DECIMAL_BASE;
		result += *buffer - VAL_OF_ZERO;
		++buffer; 
    }
    
    result *= flag;
    
    return (result);
}

char *Itoa(int n, char *buffer, int base)
{
	char *runner = NULL;
	static int LUT[36] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
	'A', 'B' ,'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
	'O' ,'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    assert(NULL != buffer);
    assert(BINARY_BASE <= base);
    assert(MAX_BASE >= base);
    
    runner = buffer;
   
	if (DECIMAL_BASE == base)
	{
		sprintf(buffer, "%d", n);
		return (buffer);
	}
	
	while (0 != n)
	{
		*runner = LUT[(n % base)];
		n /= base;
		++runner;
	}

	*runner = '\0';

	ReverseString(buffer, (size_t)(runner - buffer));
 
    return (buffer);
}

static void ReverseString(char *dest, size_t size)
{
	char *start = dest;
	char *end = dest + size - 1;
	char tmp = '\0';

	while (start < end)
	{
		tmp = *start;
		*start = *end;
		*end = tmp;
		++start;
		--end;
	}
}


    

