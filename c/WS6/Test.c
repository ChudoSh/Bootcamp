#include <stdio.h> /*printf*/	
#include "Bitwise.h"


void Exer1();
void Exer2Loop();
void Exer2NoLoop();
void Exer3();
void Exer4();
void Exer5Loop();
void Exer5NoLoop();
void Exer6a();
void Exer6b();
void Exer6c();
void Exer7();
void Exer8();
void Exer9NoLoop();
void Exer9Loop();
void Exer10();



int main()
{	
	Exer1();
	Exer2Loop();
	Exer2NoLoop();
	Exer3();
	Exer4();
	Exer5Loop();
	Exer5NoLoop();
	Exer6a();
	Exer6b();
	Exer6c();
	Exer7();
	Exer8();
	Exer9Loop();
	Exer9NoLoop();
	Exer10();
	return 0; 
	
}

void Exer1()
{
	if(Pow2(5,2) == 20)
	{
		printf("Test 1 Exer 1 - Success!\n");
	}
	else
	{
		printf("Test 1 Exer 1 - Failed..\n");
	}
	
	if(Pow2(4,2) == 16)
	{
		printf("Test 2 Exer 1 - Success!\n");
	}
	else
	{
		printf("Test 2 Exer 1 - Failed..\n");
	}
	
	if(Pow2(3,2) == 12)
	{
		printf("Test 3 Exer 1 - Success!\n\n");
	}
	else
	{
		printf("Test 1Exer 2 - Failed..\n");
	}
	
}
void Exer2Loop()
{
	if(!IsPow2_Lp(5))
	{
		printf("Test 1 Exer 2 Looped - Success!\n");
	}
	else
	{
		printf("Test 1 Exer 2 Looped  - Failed..\n");
	}
	
	if(IsPow2_Lp(8))
	{
		printf("Test 2 Exer 2 Looped  - Success!\n");
	}
	else
	{
		printf("Test 2 Exer 2 Looped  - Failed..\n");
	}
	
	
	
}
void Exer2NoLoop()
{
	if(!IsPow2_Lp(5))
	{
		printf("Test 1 Exer 2 Not Looped - Success!\n");
	}
	else
	{
		printf("Test 1 Exer 2 Not Looped - Failed..\n");
	}
	
	if(IsPow2_Lp(8))
	{
		printf("Test 2 Exer 2 Not Looped - Success!\n\n");
	}
	else
	{
		printf("Test 2 Exer 2 Not Looped- Failed..\n");
	}
}
void Exer3()
{
	if(AddOne(5) == 6)
	{
		printf("Test 1 Exer 3 - Success!\n\n");
	}
	else
	{
		printf("Test 1 Exer 3 - Failed..\n");
	}
	
	if(AddOne(345) == 346)
	{
		printf("Test 2 Exer 3 - Success!\n\n");
	}
	else
	{
		printf("Test 2 Exer 3 Failed..\n");
	}
}
void Exer4()
{
	unsigned int arr[] = {9,28,2,7,4,6,112};	
	
	printf("If test For Exer 4 is succesful yhthe return should be 28,7 and 112.\n");
	
	ThreeBit(arr, 7);
	
	printf("\n");
}

void Exer5Loop()
{
	
	printf("If successful test For Exer 5 should retrun the opposite of 1 which is 128.\n");
	
	printf("Result for Exer 5 looped is %u\n\n",ByteMirrors_LP((unsigned char)1));

}
void Exer5NoLoop()
{
	printf("If successful test For Exer 5 unlooped should retrun the opposite of 1 which is 128.\n");
	
	printf("Result for 5 unlooped is %u\n\n",ByteMirrors_No_LP((unsigned char)1));
}
void Exer6a()
{
	printf("If successful test 1 For Exer 6a retrun 1 for the number 39.\n");
	
	printf("Result for test 1 Exer 6a is %u\n\n",BothTwoSix((unsigned char)39));
	
	printf("If successful test 2 For Exer 6a retrun 0 for the number 66.\n");
	
	printf("Result for test 2 Exer 6a is %u\n\n",BothTwoSix((unsigned char)66));
}

void Exer6b()
{
	printf("If successful test 1 For Exer 6b retrun 1 for the number 7.\n");
	
	printf("Result for Exer 6b test 1 is %u\n\n",EitherTwoSix((unsigned char)7));
	
	printf("If successful test 2 For Exer 6b retrun 1 for the number 66.\n");
	
	printf("Result for Exer 6b test 2 is %u\n\n",EitherTwoSix((unsigned char)66));
}

void Exer6c()
{

	printf("If successful test For Exer 6c retrun 199 for the number 211.\n");
	
	printf("Result for Exer 6c is %u\n\n",SwapThreeFive((unsigned char)211));
	
}

void Exer7()
{

	printf("If successful test For Exer 7 will retrun 68 for the number 64.\n");
	
	printf("Result for Exer7 is %u\n\n",HexaDec(68));
	
}

void Exer8()
{
	unsigned int x = 90;
	unsigned int y = 60;
	unsigned int *p = &x;
	unsigned int *q = &y;
	
	
	printf("If successful test For Exer 8 will retrun 60 for the value of x.\n");
	
	SwapValues(p,q);
	
	printf("Result for x is %u\n\n",x);
}
void Exer9Loop()
{
	printf("If successful test For Exer 9 with loop  for the number  84 will retrun 3.\n");
	
	printf("Result for 9 with loop is %u\n\n", CountBit(84));
	
}

void Exer9NoLoop()
{
		printf("If successful test For Exer 9 no loop for the number 84 will retrun 3.\n");
	
	printf("Result for 9 no loop is %u\n\n", CountNumBits_No_Lp(84));

}

void Exer10()
{
	printf("READ FROM LEFT TO RIGHT -Result for Exer 10 when the float is 11.1 is ");

	BitFloat(11.1);
	

}



