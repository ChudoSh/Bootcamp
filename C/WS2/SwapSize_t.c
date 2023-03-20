#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void SwapSize_t(size_t *p, size_t *q);
void SwapSize_t_Pointers(size_t **p, size_t **q);

void main()
{
	size_t a = 67, b = 123; 
	size_t *p = &a, *q = &b;
	size_t **p2 = &p, **q2 = &q;
	SwapSize_t_Pointers(p2, q2); 
	
	printf("%ld\n", a);
	
}


void SwapSize_t(size_t *p, size_t *q)
{
	assert(p != 0 || q != 0);
	size_t flag = *p; 
	*p = *q; 
	*q = flag;		
}

void SwapSize_t_Pointers(size_t **p, size_t **q)
{
	
	assert(p != 0 || q != 0);
	SwapSize_t(*p, *q);	
}


