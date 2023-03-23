/* 
Dev: BarSH
Rev: 
Staus:
Date of latest update:
*/


#include <stdio.h> /*print*/
#include <stdlib.h> 
#include <assert.h> /*assert*/
#include <string.h> /*To test the functions*/
#include <ctype.h>
#include <strings.h> 
#include "Strings.h" /* My functions*/


int main(int argc, char[] argv)
{

	char str1[50] = "banana";
	char str2[50] = "BANANA";
	char str3[50] = "Etai the king";
	char *str4 = "b";
	
	char *str8 = "123321";

	char str1test1[100];
	char str2test1[100];
	char str3test1[100]; 
	char str4test1[100];
	char *str6test; 
	
	

/**********Tests for StrCpy, StrNCpy, StrCmp,StrNCmp********/ 
	/*if(0 == StrCmp(strcpy(str1test1,str1), StrCpy(str2test1,str1)))
	{
		printf("Test 1 using StrCmp for StrCpy - Success!\n");
		
	}
	else
	{
		printf("Test 1 for StrCpy Failed\n");
	}
	
	
	
	if(0 == StrCmp(strcpy(str3test1,str2), StrCpy(str4test1,str2)))
	{
		printf("Test 2 using StrCmp for StrCpy - Success!\n");
		
	}
	
	else
	{

		printf("Test 2 for StrCpy Failed\n");
	}*/
/*************End for StrCpy, StrNCpy, StrCmp,StrNCmp*************************************/	

***************Test for StrCHr**********************************/	
	if(strchr(str1,'\0') == StrChr(str1,'\0'))
	{
		printf("strchr and StrChr results are the same, Success!\n");
	}
	else
	{
		printf("StrCh Test Failed\n");
	}
	
/*****************End StrChr****************/


/*********************Test for StrCaseCmp************************/	
	if(strcasecmp(str1,str2) == StrCaseCmp(str1,str2))
	{
		printf("Results for strcasecmp and StrCaseCmp are the same - Success!\n");
	}
	else
	{
		printf("StrCaseCmp Test Failed\n");
	}
	
	
/*******************Test for StrDup****************************/

	str6test = StrDup(str3);
	
	if(0 == StrCmp(str3, str6test))
	{
		printf("Test 1 using for StrDup - Success!\n");
		
		free(str6test);
		str6test = NULL;
		
	}
	
	else
	{

		printf("Test 1 for StrCpy Failed\n");
	}
	
/*************End********************/

/********Test for StrCat and StrNcat****************/

	if(0 == StrCmp(strncat(str1,str2,3), StrNCat(str1,str2,3)))
	{
		printf("Test for StrCat and StrNCat - Success!\n");
	}
	else
	{

		printf("Test for StrCat and StrNCat Failed\n");
	}


/**********End StrCat and StrNCat**************/

/********Test for Strstr****************/


	if(strstr(str3,str4) == StrStr(str3,str4))
	{
		printf("Test for StrStr - Success!\n");
	}
	else
	{

		printf("Test for StrStr Failed\n");
	}




/********End for Strstr****************/
	
/*****Test fot Strspn************/

	if(strspn(str3,str4) == StrSpn(str3,str4))
	{
		printf("Test for StrSpn - Success!\n");
	}
	else
	{

		printf("Test for StrSpn Failed\n");
	}

	printf("Is %s Pali? %d\n", str8,StrPali(str8));  
	
	
	SevenBoom(157, 217);

	
	return 0;
}

