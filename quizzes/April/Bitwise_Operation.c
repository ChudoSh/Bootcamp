#include <stdio.h>
#include <string.h>

/*EXER 1*/
int CheckCoupleBit(int n)
{
	size_t count = 0; 
	
	while (0 < n)
	{
		if(3 == (n & 3))
		{
			++count; 
		}
		
		n >>= 1;
	}
	
	return count;
}


/*EXER 2*/
void SwapByPointer(int a, int b)
{
	if (*a != *b)
	{
		*a = *a + *b;
		*b = *a - *b;
		*a = *a - *b;	
	}
	
} 
int SwapByTemp(int *a, int *b)
{
	int temp = 0;
	
	if (*a != *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
	
	
} 
void SwapByBitwise(int *a, int *b)
{
	if (*a != *b)
	{
		*a = *a ^ *b;
		*b = *a ^ *b;
		*a = *a ^ *b;
	}
} 

/*EXER 3*/
int Kernighan(int num)
{
	int count = 0;
	
	while (0 != num)
	{
		n = n & (n - 1);
		++count;
	} 
	
	return count;
} 


int main()
{
	printf("%d\n",CheckCoupleBit(118));
	
	return 0; 	
}
