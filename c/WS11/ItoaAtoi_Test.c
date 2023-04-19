/*
Dev: BarSh
Rev: MariaP
Status: Approved
Date: 19.4.23
*/

#include <stdio.h>/*printf*/
#include <string.h>/*strcmp*/
#include <stdlib.h> /*itoa*/

#include "ItoaAtoi.h"


int main()
{
    int test1 = 0xFB4F;
    char buffer1[1000];
    
    int test2 = 0;
    char buffer2[1000] = "  -12a";
    
   	Itoa(test1, buffer1, 16);
    test2 = Atoi(buffer2);
    
    if (0 ==  strcmp("FB4F",buffer1))
    {
    	printf("Sucess for Itoa; the given number was 0xFB4F \n");
    }
    else
    {
    	printf("Failed for Itoa..  %s\n",buffer1);
    }
    
    if (atoi(buffer2) == test2)
    {
		printf("Sucess for Atoi, the string tested was '    -12' %d\n", test2);
	}
	else
	{	
		printf("Failed for Atoi..  %d\n",atoi("    -12.3"));
	}	
	
	printf("%d\n", atoi("  -12a"));
    
    return 0;
}
