#include <stdio.h>

void Swap(int *p, int *q);

void main()
{
	int a = 1, b = 10; 
	int *p = &a, *q = &b;
	Swap(p, q); 
	
	printf("%d\n", a);
}


void Swap(int *p, int *q)
{
	int flag = *p; 
	*p = *q; 
	*q = flag;		
}

