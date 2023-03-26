#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef void (*funcpt)();
funcpt LUT[256];

void PressA()
{
	printf("A-Pressed\n");
	
}

void PressT()
{
	printf("T-Pressed\n");		
	
}
void PressESC()
{
	abort();		
}

void PressNULL()
{
	
}

void SetLut(funcpt LUT[])
{
	int i = 0;
	
	for(i = 0; i < 256; ++i)
	{	
	 	LUT[i] = PressNULL;
	}
		
	LUT['A'] = PressA;
	LUT['T'] = PressT;
	LUT[27] = PressESC;
		
}

int main(int argc, char* argv[])
{			
		
		int c = 0;
		
		SetLut(LUT);
			
	 	scanf("%c\n", &c);
	 	LUT[c]();
	
		return 0; 			
}
