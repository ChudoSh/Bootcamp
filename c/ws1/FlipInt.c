#include <stdio.h>

int FlipInt(int n);

void main()
{

	printf("%d\n", FlipInt(-3456));
	
}

int FlipInt(int n)
{
	int flag = 0;
	int result = 0;
	
	if(n < 0)
	{
		flag = 1;
		n = -n;
	}
		
	while(n > 9)
	{
		result = result*10 + n%10;
		n = n/10;		
	}
	
	return flag ? -(result*10 + n) : result*10 +n; 
}
