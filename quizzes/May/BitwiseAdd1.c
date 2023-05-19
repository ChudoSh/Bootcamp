#include <stdio.h>/*printf*/


unsigned int BitwiseIncrementOne(unsigned int x);

int main()
{
	int test = 1;
    
	if (2 == test)
    {
		printf("Sucess for increment \n");
	}
	
	else
	{	
		printf("fail for increment..  \n");
	}
	
	return (0);	
}

unsigned int BitwiseIncrementOne(unsigned int x)
{
   int mask = 1; 
   
	while (x & mask)
	{	
		x ^= mask;
		mask <<= 1;
    }
   
   return (x |= mask);
}
