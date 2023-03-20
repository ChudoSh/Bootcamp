#include <stdio.h>
/*
Dev: BarSh
Rev: EtaiSH
Status: Tested By Alon
Date: 19.3.23
*/



int FlipInt(int n);

int main()
{

	if( 1234 == FlipInt(4321))
	{
		printf("Success!\n");
	}
	
	return 0; 
	
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
		result = result * 10 + n % 10;
		n = n / 10;		
	}
	
	return flag ? -(result * 10 + n) : result * 10 + n; 
}
