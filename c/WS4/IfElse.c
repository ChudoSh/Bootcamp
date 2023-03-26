



#include <stdio.h>/*prinf*/
#include <assert.h>/*asert*/
#include <stdlib.h> /*abort*/

#define ESC 27

void PressAT(char *c)
{
	
	assert(NULL != c);

	scanf("%c",c);
	
	if('A' == *c)
	{
		printf("A-Pressed\n");
	}
	else if('T' == *c)
	{
		printf("T-Pressed\n");
	}	
	else if(ESC == *c)
	{
		abort();
	}
}



int main(int argc, char* argv[])
{			
		char str[1] = "";
		
		PressAT(str);
		
		return 0; 			
}
