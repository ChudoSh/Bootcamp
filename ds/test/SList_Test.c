/*
Dev: BarSH
Rev: 
Date: 
Status: 
*/

#include <stdio.h>

#include "SList.h"

int main()
{
	int x = 5; 
	iter_t i = NULL;
	
	slist_t *list = SListCreate();
	
	i = SListBegin(list);	 
	
	SListInsert(i, &x);
	
	printf("%d\n", *((int*)SListGet(i)));
		
	SListDestroy(list);

	return (0);
}
