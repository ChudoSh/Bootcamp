#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

char* CpArr(char *ArrToCopy, int SIZE);

void main()
{	 
	
	char Original[] = {'a','b','\0'};
	char *p = Original;
	char *Copy = CpArr(p, 3);
	printf("%s\n", Copy);
	
}


char* CpArr(char *ArrToCopy, int SIZE) //The function returns a char type pointer and receives 
				       //a pointer to a char array and its size				
{	 
	char *p = (char*)malloc(SIZE * sizeof(int)); //Allocating the memory of the array 
						    // to the pointer
	assert(ArrToCopy != 0);					 
						 
	int i; //Defining the index for the loop
	

	for(i = 0; i < SIZE; i++) //Looping over the array and assinging the address to the pointer
	{
		p[i] = ArrToCopy[i]; 
		
	}
	
	return p; 
				
}

