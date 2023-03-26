/*
Dev:BarSH
Rev:AlonL
Date:26.3.23
Status:Approved
*/


#include <stdio.h>/*printf*/
#include <stdlib.h>/*system*/

#define ESC 27
#define KEY1 'A'
#define KEY2 'T'
#define STOP 0
#define CONTINUE 1

typedef int (*funcpt)();
funcpt LUT[256];

static int PrintA()
{
	printf("A-Pressed\n");
	return CONTINUE;
}

int PrintT()
{
	printf("T-Pressed\n");	
	return CONTINUE;	
}
static int PressESC()
{
	return STOP;		
}

static int DoNothing()
{
	return CONTINUE;
}

void SetLut(funcpt LUT[])
{
	int i = 0;
	
	for(i = 0; i < 256; ++i)
	{	
	 	LUT[i] = DoNothing;
	}
		
	LUT[KEY1] = PrintA;
	LUT[KEY2] = PrintT;
	LUT[ESC] = PressESC;
		
}

int main(int argc, char* argv[])
{		
		
		system("stty -icanon -echo"); 	
		SetLut(LUT);
		  
		while(1)
		{
				
			char input = '\0';
			input = getchar();
	 	
	 		if(STOP == LUT[input]())
	 		{
	 			break;
	 		}
		
		}
		system("stty icanon echo"); 
		
		
	
		return 0; 			
}
