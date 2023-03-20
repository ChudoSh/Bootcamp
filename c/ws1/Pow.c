#include <stdio.h>

double Pow(int n);


void main()
{
	printf("%f\n",Pow(-5));	
}


double Pow(int n)
{
	double result = 1, base = 10; 

	if(n < 0)
	{
		n = -n;
		base = 0.1;
	}

	for(int i = 0; i < n; ++i)
	{
		result *= base;
	}
	
		return result;
}
