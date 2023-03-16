#include <stdio.h>

int flipint(int n);

void main()
{

	printf("%d\n", flipint(-3456));
	
}

int flipint(int n)
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
