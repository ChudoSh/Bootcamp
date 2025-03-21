#include <stdio.h>
#include <assert.h>

enum RESULT
{
	SUCCESS = 0
};

long *ArrayOfIntsToLong(int *ints, size_t NumOfElements)
{
	size_t i = 0;

	assert(NULL != ints);
	
	for (i = 0; i <= (NumOfElements) / 2; ++i)
	{
		*((long *)ints[i]) = ((long)ints[i * 2] + (long)ints[i * 2 + 1]);
	}
	
	return ((long *)ints);	
}

int main()
{
	int arr[] = {1, 2, 4, 5, 8 ,9, 1,2};
	int i = 0;
	long *longarr = (long *)arr;
	ArrayOfIntsToLong(arr, 8);
	
	for (i = 0; i < 4; ++i)
	{
		printf("%lu\n",longarr[i]);
	}
	
	printf("%lu\n",sizeof(longarr[0]));
	
	return (SUCCESS);
}
