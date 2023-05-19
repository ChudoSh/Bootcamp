#include <stdio.h>/*printf*/
#include <string.h>/*strcmp*/
#include <stdlib.h> /*itoa*/

enum UTILS 
{
	MULT_TEN = 10,
	CHAR_CONVERT = 48
};

int Atoi(const char *buffer);

int main()
{
	int test = 0;
    char buffer[1000] = "  -12a";
    
	if (atoi(buffer) == test)
    {
		printf("Sucess for Atoi, the string tested was '    -12' %d\n", test2);
	}
	
	else
	{	
		printf("Failed for Atoi..  %d\n",atoi("    -12.3"));
	}
	
	return (0);	
}

int Atoi(const char *buffer)
{
    int flag = 1; 
    int result = 0;

    assert(NULL != buffer);
	   
    while (' ' == *buffer && '\0' != *buffer)
    {
		++(buffer);
    }
   
	if ('-' == *buffer)
	{
		++(buffer);
	    flag = -1;
    } 
	 		
    while (isdigit(*buffer))
    {
		result *= MULT_TEN;
		result += *buffer - CHAR_CONVERT;
		++(buffer); 
    }
    
    result *= flag;
    
    return (result);
}
