
#include <stdio.h>

#include "ListExercise.h"

int main()
{
	int x = 5; 
	float a = 6;
	double b = 7;
	char u = 'A';
	
	iter_t i = NULL;
	
	slist_t *list = SListCreate();
	
	i = SListBegin(list);
	
	SListInsert(i, &x);
	printf("%d\n", *((int*)SListGet(i)));
	i = SListNext(i);
	SListInsert(i, &a);
	printf("%f\n", *((float*)SListGet(i)));
	i = SListNext(i);
	SListInsert(i, &b);
	printf("%f\n", *((double*)SListGet(i)));
	i = SListNext(i);
	SListInsert(i, &u);
	printf("%c\n", *((char*)SListGet(i)));
	
	printf("%lu\n", SListCount(list));
	
	SListDestroy(list);

	return (0);
}
