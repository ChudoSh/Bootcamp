/*

Dev: BarSH
Rev: EtaiSH
Status: Approved
Date: 26.3.23

*/

#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc()*/
#include <stdio.h> /*printf*/

#define STOP -1

size_t Flavius(size_t num_People);

int main()
{	  

	printf("%ld\n",Flavius(100));
	
	return (0);
}

size_t Flavius(size_t num_People)
{
	size_t i = 0;
	size_t *sword = malloc(sizeof(size_t) * num_People);
	
	if(0 == num_People)
	{
		printf("No people inserted");
		return STOP;
	}
	
	if(NULL == sword)
	{
		printf("Didnt allocate properly");
		return STOP;
	}
	
	for(i = 0;i < num_People - 1; ++i)
	{
		sword[i] = i + 1;
	}
	
	sword[i] = 0; 
	i = 0;
	
	while(i != sword[i])
	{
		sword[i] = sword[sword[i]];
		i = sword[i];	
	}
	
	free(sword);
	sword = NULL;
	
	return i;
	
}

