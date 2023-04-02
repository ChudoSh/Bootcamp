/*
Dev:BarSH
Rev:b ShlomiA
Date: 2.4.23
Status: Approved
*/

#include <stdio.h> /*printf*/	
#include "Bitwise.h"

#define SIZE_INT 32
#define SIZE_CHAR 8
#define SIZE_LUT 256
#define ONE 1
#define NONE 0
#define TRUE34 34
#define TRUE240 240


/*EXER 1*/
long Pow2(unsigned int x, unsigned int y)
{
	return (x << y); 
}
/**/

/*EXER 2 WITH LOOP*/
unsigned int IsPow2_Lp(unsigned int n)
{
	size_t i = 1;
	
	while(i <= SIZE_INT)
	{
		if((unsigned)(1 << i) == n)
		{
			return ONE;
		}
		++i;
	}
	return NONE;
	
	
	
}
/**/

/*EXER 2 WITHOUT LOOP*/
unsigned int IsPow2_No_Lp(unsigned int n)
{

	if((n & (n - 1)))
	{
		return ONE;
	}
	return NONE; 
	
}
/**/

/*EXER 3*/
unsigned int AddOne(unsigned int n)
{	
	int Add = 1; 

	while((n & Add))
	{
		n = n ^ Add;
		Add = Add << 1;
	}
	n = n ^ Add;
	
	return n; 
	
}	
/**/

/* EXER 4 - ALSO USED IN EXER 9 WITH LOOP*/
unsigned int CountBit(unsigned int n)
{
	int count = 0; 
	size_t i = 0;
	
	for(i = 0; i < SIZE_INT; ++i)
	{
		if(n & (1 << i))
		{
			++count;
		}
		
	}
	
	return count; 	
	
}
 
void ThreeBit(unsigned int n[], size_t size)
{
	size_t i = 0;
	
	if(NULL == n)
	{	
		perror("Invalid pointer.\n");
		
	} 
	
	while(i < size)
	{
		if(3 == CountBit(*n))
		{
			printf("The number with exactly 3 bits is %u in the address %u\n",*n ,n[i]);
		}
		++i;
		++n;
	}
}
/**/

/*EXER 5 WITHLOOP*/
unsigned char ByteMirrors_LP(unsigned char n)
{
    unsigned int output = 0;	
	unsigned int temp = 0; 
	size_t i = 0;
	
	for(i = 0; i < SIZE_CHAR; ++i)
	{
		output = output << 1; 
		temp = n & 1; 
		output = output | temp;
		n = n >> 1;
	}
	
	return output; 	
	
}
/**/

/*EXER 5 NO LOOP*/
unsigned char ByteMirrors_No_LP(unsigned char n)
{
    static int LUT[SIZE_LUT] = {0};
	size_t i = 0; 
	static int flag = 0;
	
	if(NONE == flag)
	{
		for(i = 0; i < SIZE_LUT; ++i)
		{
			LUT[i] = ByteMirrors_LP(i);
		}
		
	flag =  ONE; 
	
	}
	
	return LUT[n];	
	
}
/**/

/*EXER 6*/
/*A*/
unsigned int BothTwoSix(unsigned char n)
{

	return ((n & TRUE34) == TRUE34);

}

/*B*/
unsigned int EitherTwoSix(unsigned char n)
{

	return ((n & (32)) || (n & (2)));

}

/*C*/
unsigned int SwapThreeFive(unsigned char n)
{	
	unsigned int temp1 = 0; 
	unsigned int temp2  = 0;
	
	
	temp1 = n & 16; 
	temp2 = n & 4;
	n = n & (~20);
	n = n | (temp1 >> 2);
	n = n | (temp2 << 2);
	
	
	return n; 	
}
/**/

/*EXER 7*/
unsigned int HexaDec(unsigned char n)
{

	return ((unsigned int)n & TRUE240);

}
/**/ 

/*EXER 8*/
void SwapValues(unsigned int *p,unsigned int *q )
{
	if(*p == *q)
	{
		printf("The values are equal, nothing to swap.\n");
	}	
	
	else
	{
		*p = *p ^ *q;
		*q = *p ^ *q;
		*p = *p ^ *q;
	}
}
/**/

/*EXER 9*/

/*WITH LOOP - SEE EXER 4*/
	
/*WITHOUT LOOP*/ 
unsigned int CountNumBits_No_Lp(unsigned int n)
{
	static int LUT[SIZE_LUT] = {0};
	unsigned int i = 0;
	static int flag = NONE;

	if(NONE == flag)
	{
		for(i = 0; i < SIZE_LUT; ++i)
		{
			LUT[i] = CountBit(i);
		} 
		
		flag = ONE;
	}
	
	return LUT[n]; 
}

/**/

/*EXER 10*/
void BitFloat(float num)
{
    int i = 0;
    unsigned int *p = NULL;
    
    p = (unsigned int*)&num;
    
    for(i = 0;i < SIZE_INT; ++i)
   	{
    	printf("%d", *p & 1);
    	*p = *p >> 1;
    }
 
    printf("\n"); 
}
	


