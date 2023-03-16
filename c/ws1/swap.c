#include <stdio.h>

void swap(int *p, int *q);

void main()
{
	int a = 1, b = 10; 
	int *p = &a, *q = &b;
	swap(p, q); 
	
	printf("%d\n", a);
}


void swap(int *p, int *q)
{
	int flag = *p; 
	*p = *q; 
	*q = flag;		
}

