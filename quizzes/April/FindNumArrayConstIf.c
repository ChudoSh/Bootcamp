#include <stdio.h>

enum RESULT
{
	FAIL = -1,
	SUCCESS = 0
};

int FimdNumArrayConstIf(int *arr, size_t size, int x)
{
	
	while (*arr != x && 0 < size)
	{
		++arr;
		--size;
	}
	
	if (*arr != x)
	{
		return (FAIL); 
	}
	
	return (SUCCESS); 	
}

int main()
{
	int arr[8] = {1, 3, 5,6,7,8,9,10};
	
	if (SUCCESS == FimdNumArrayConstIf(arr, 8, 1))
	{
		printf("Success!\n");
	}
	
	return (SUCCESS);
}



