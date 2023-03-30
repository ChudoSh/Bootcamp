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

/*EXER 2 WITHOUT LOOP*/
unsigned int IsPow2_Lp(unsigned int n)
{
	unsigned int i = 1;
	
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

/*EXER 2 WITH LOOP*/
unsigned int IsPow2_No_Lp(unsigned int n)
{

	if((n & (n-ONE)) == NONE)
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

	while(ONE == (n & Add))
	{
		n = n ^ Add;
		Add = Add << 1;
	}
	n = n ^ Add;
	
	return n; 
	
}	
/**/

/* EXER 4*/
unsigned int CountThreeBit(unsigned int n)
{
	int count = 0; 
	int i = 0;
	
	for(i = 0; i < SIZE_INT; ++i)
	{
		if(n & (1 << i))
		{
			++count;
		}
		
	}
	
	return count; 	
	
}
 
void ThreeBit(unsigned int *n, size_t size)
{
	size_t i = 0;
	
	if(NULL == n)
	{	
		perror("Invalid pointer.\n");
		
	} 
	
	while(i < size)
	{
		if(3 == CountThreeBit(*n))
		{
			printf("Index with exactly 3 bits is %u\n", *n);
		}
		++i;
		++n;
	}
}
/**/

/*EXER 5 WITHLOOP*/
unsigned int ByteMirror_LP(unsigned n)
{
    unsigned int output = 0;	
	unsigned int temp = 0; 
	int i = 0;
	
	for(i = 0; i < SIZE_CHAR; ++i)
	{
		temp = n & 1; 
		output = output | temp;
		output = output << 1; 
		n = n >> 1;
	}
	
	return output; 	
	
}
/**/

/*EXER 5 NO LOOP*/
unsigned int ByteMirror_No_LP(unsigned n)
{
    static int LUT[SIZE_LUT] = {0};
	int i = 0; 
	static int flag = NONE;
	
	if(NONE == flag)
	{
		for(i = 0; i < SIZE_LUT; ++i)
		{
			LUT[i] = ByteMirror_LP(i);
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

	return (((unsigned int)n & (1 << 1)) && ((unsigned int)n & (1 << 1)));

}

/*B*/
unsigned int EitherTwoSix(unsigned char n)
{

	return (((unsigned int)n & (1 << 1)) || ((unsigned int)n & (1 << 1)));

}

/*C*/
unsigned int SwapThreeFive(unsigned char n)
{	
	unsigned int temp1 = 16; 
	unsigned int temp2  = 4;
	
	n = n & (~20);
	n = n | temp1 >> 2;
	n = n | temp2 << 2;
	
	
	return n; 	
}
/**/

/*EXER 7*/
unsigned int HexaDec(unsigned char n)
{

	return ((unsigned int)n & 240);

}
/**/ 

/*EXER 8*/
void SwapValues(unsigned int *p,unsigned int *q )
{
	/*This will work only when *p != *q, else will return 0;*/
	
	*p = *p ^ *q;
	*q = *p ^ *q;
	*p = *p ^ *q;
}
/**/

/*EXER 9*/

/*WITH LOOP*/
unsigned int CountNumBits_LP(unsigned int n)
{
	unsigned int count = 0; 
	int i = 0; 
	
	for(i = 0;i < SIZE_CHAR;++i)
	{
		if((n & 1) == 1)
		{
			++count;
			n = n >> 1;
		}
	}
	
	return count; 
	
}	
/*WITHOUT LOOP*/ 
unsigned int CountNumBits_No_Lp(unsigned int n)
{
	static int LUT[SIZE_CHAR] = {0};
	unsigned int i = 0;
	static int flag = NONE;
	
	if(NONE == flag)
	{
		for(i = 0; i < SIZE_CHAR; ++i)
		{
			LUT[i] = CountNumBits_LP(i);
		} 
		
		flag = ONE;
	}
	
	return LUT[n]; 
}

/**/

/*EXER 10*/
void BitFloat(float num)
{
    int i = NONE;
    unsigned int *p = NULL;
    
    p = (unsigned int*)&num;
    
    for(i = 0;i < SIZE_INT; ++i)
   	{
    	printf("%d", *p & ONE);
    	*p = *p >> ONE;
    }
 
    printf("\n"); 
}
	


