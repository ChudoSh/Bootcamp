#include <stdio.h>

enum RESULT
{
	FAIL = -1,
	SUCCESS = 0
};

RESULT FimdNumArrayConstIf(int *arr, size_t size, int x)
{
	while (*arr != x || 0 < size)
	{
		++arr;
		--size;
	}
	
	if (*arr == x)
	{
		return (SUCCESS); 
	}
	
	return (FAIL); 	
}

int main()
{
	size_t i = 0;
	char c = '\0'; 
	
	for (i = 0; i < 10; ++i)
	{
		scanf("%c", &c);
		OneMillionChars(c);
	}
	  
	return 0;

}



