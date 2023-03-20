#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

char *CpArr(char *ArrToCopy, int SIZE);

void main()
{	 
	
	char Original[] = {'a','b','\0'};
	char *p = Original;
	char *Copy = CpArr(p, 3);
	
	printf("%s\n", Copy);
	free(Copy);
	
	Copy == NULL; 
	
}


char *CpArr(char *ArrToCopy, int SIZE) 	
{	 
	char *p = (char*)malloc(SIZE * sizeof(int)); 
	int i = 0;
						   
	assert(0 != ArrToCopy);					 
						 
	

	for(i = 0; i < SIZE; ++i) 
	{
		p[i] = ArrToCopy[i]; 
		
	}
	
	return p; 
				
}

