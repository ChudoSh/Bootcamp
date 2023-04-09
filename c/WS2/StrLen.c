#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

size_t StrLen(const char *r);

void main()
{
	char c[] = {'B','a','n','a','n','a','\0'};
	char *p = c;
	
	printf("%ld\n",StrLen(p)); 
}


size_t StrLen(const char *r)
{

	assert(0 != r);
	
	size_t i = 0;
	
	while (*(r + i) != '\0')
	{
		 i++; 
	}	

	return i;
}

