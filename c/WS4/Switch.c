#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define ESC 27

void PressAT(char *c)
{
	
	assert(NULL != c);

	scanf("%c",c);
	switch (*c)
	{
		case 'A':
			printf("A-Pressed\n");
			break;
		case 'T':
			printf("T-Pressed\n");
			break;
		case ESC:
			abort();
	}
}



int main(int argc, char* argv[])
{			
		char str[1] = "";
		
		PressAT(str);
		
		return 0; 			
}
