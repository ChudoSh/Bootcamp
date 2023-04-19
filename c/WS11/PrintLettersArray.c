#include <stdio.h>
#include <string.h>
#include <assert.h>

enum PRINT
{
	PRESENT = 1,
	PRINT = 2,
	DONT_PRINT = 3
};

#define ASCII_SIZE 256


void PrintLettersArray(const char *str1, const char *str2, const char *str3);

int main()
{
	PrintLettersArray("abcdef", "abcdg", "a");
	
 	return 0; 	
}



void PrintLettersArray(const char *str1, const char *str2, const char *str3) 
{
	size_t i = 0; 
	int LUT[ASCII_SIZE] = {0};
	
	assert(NULL != str1);
	assert(NULL != str2);
	assert(NULL != str3);
	
	while ('\0' != *str1)
	{
		LUT[(int)*str1] = PRESENT;
		++str1;
	}
	
	while ('\0' != *str2)
	{
		if (PRESENT == LUT[(int)*str2])
		{
			LUT[(int)*str2] = PRINT;
		}
		
		++str2;
	}
	
	while ('\0' != *str3)
	{
		if (PRINT == LUT[(int)*str3])
		{
			LUT[(int)*str3] = DONT_PRINT;
		}
				
		++str3;
	}
	
	for(i = 0; i < ASCII_SIZE; ++i)
	{
		if (PRINT == LUT[i])
		{
			printf("%c\n", (char)i);
		}
	}
	
}






