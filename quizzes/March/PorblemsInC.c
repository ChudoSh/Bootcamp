#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>/*This was missing in the code thus no strlen or string copy*/

int main()
{
	char *str1 = "hello";
	/*char str2[strlen(str1)];*//*Cannot declare a string this way, C forbids defining an array size using a variable*/
	char *str3 = (char*)malloc(strlen(str1) + 1);
	/*Missing library for strlen, also here, C forbids defining an array size using a variable*/
	
	while(*str1)
	{
		*str3 = *str1; 
		++str3;
		++str1;			
	}
	
	/*strcpy(str2,str1);*//*Missing library to use this function*/
	
	if(islower(*str1))/*will not enter the if since the pointer points to the termination character*/ 
	{
		*str1 = toupper(*str1);
	}
	
	free(str3);/*Memory cannot be freed since it is not set to the start of the string*/
	str3 = NULL;
	
	return	0;
	/*No return in the program since int main*/
}
