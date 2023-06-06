#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void GenericSwap(void *a, void *b, size_t size)
{
	char temp = '\0';
	
	assert(NULL != a);
	assert(NULL != b);
	
	while (0 < size)
	{
		temp = *(char *)a; 
		*(char *)a = *(char *)b;
		*(char *)b = temp;
		 
		a = (void *)(((char *)a + 1));
		b = (void *)(((char *)b + 1));
		--(size);
	}
} 

int main()
{
	int x = 6; 
	int y = 10; 
	
	GenericSwap(&x, &y, sizeof(int));
	
	printf("This is x: %d, and this is y: %d\n", x,y);

	return (0);
}
