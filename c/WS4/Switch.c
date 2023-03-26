/*
Dev:BarSH
Rev:AlonL
Date:26.3.23
Status:Approved
*/



#include <stdio.h>/*printf*/
#include <stdlib.h>/*system*/


#define ESC 27
#define Key1 'A'
#define Key2 'T'
#define STOP 0
#define CONTINUE 1

static void PrintPressed(char c)
{
	printf("%c Pressed\n", c);
}
static int PressAT()
{
	char input = '\0';

	input = getchar();
	
	while(1)
	{
		switch (input)
		{
			case Key1:
			case Key2:
				PrintPressed(input);
				return CONTINUE;
			case ESC:
				return STOP;
		}
	}
}



int main(int argc, char* argv[])
{		
		system("stty -icanon -echo");
		 	
		PressAT();
		
		system("stty icanon echo"); 
		
		return 0; 			
}
