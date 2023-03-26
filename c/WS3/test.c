#include <assert.h>/*assert()*/
#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc()*/
#include <ctype.h> 
#include <string.h> /*sprintf*/
#include <stdio.h> /*printf*/

size_t LastOneStanding(size_t num_People)
{
	size_t i = 0;
	size_t *sword = malloc(sizeof(size_t) * num_People);
	
	assert(0 < num_People);
	
	for(i = 0;i < num_People; ++i)
	{
		sword[i] = i + 1;
	}
	
	sword[i] = 0; 
	i = 0;
	
	while(i != sword[i])
	{
		sword[i] = sword[sword[i]];
		i = sword[sword[i]];
	}
	
	free(sword);
	sword = NULL;
	
	return i;
	
}

int main()
{	  

	printf("%ld\n",LastOneStanding(100));
	
	return (0);
}
