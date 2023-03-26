/*
Dev:BarSH
Rev:AlonL
Date:26.3.23
Status:Approved
*/


#include <stdio.h>/*prinf*/

#define ESC 27/*We must use define*/
#define Key1 'A'
#define Key2 'T'

void PressAT() /*We dont need to receive anything in this function*/
{  
	
	while(1)
	{
		char input = '\0';
		
		input = getchar();
		
		if(Key1 == input)
		{
			printf("A-Pressed\n");
		}
		else if(Key2 == input)
		{
			printf("T-Pressed\n");
		}	
		else if(ESC == input)
		{
			break;
		}
	}
}



int main()
{		
	system("stty -icanon -echo"); 	
	
		PressAT();
		
		system("stty icanon echo"); 
		
		return 0; 			
}
