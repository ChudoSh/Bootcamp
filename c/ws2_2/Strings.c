/* 
Dev: BarSH
Rev: TalG
Staus: Reviewed
Date of latest update: 23.2.23
*/

#include <assert.h>/*assert()*/
#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc()*/
#include <ctype.h> /*toupper*/
#include <string.h> /*sprintf*/
#include <stdio.h> /*printf*/
#include "Strings.h"

/*Part 1 Functions WS1*/

int StrCmp(const char *str1, const char *str2)
{
	assert(str1 != 0 && str2 != 0);
	
	if(StrLen(str1) < StrLen(str2))
	{
		return StrNCmp(str1,str2, StrLen(str2));
	}
	
	return StrNCmp(str1,str2, StrLen(str2));
}


size_t StrLen(const char *str)
{
	const char *start_str = NULL;
	 
	assert(NULL != str);
	
	start_str = str;
	
	while ('\0' != *str)
	{
		 ++str; 
	}	

	return (size_t)(str - start_str);
}


/* Part 2 Functions Ws2*/

char *StrCpy(char *dest_str, const char *src_str)
{

	assert(NULL != src_str && NULL != dest_str);
	
	StrNCpy(dest_str, src_str, StrLen(src_str)+1); 
	
	return dest_str;

}




char *StrNCpy(char *dest_str, const char *src_str, size_t num_to_copy)
{
	char *start = NULL;
	
	assert(NULL != src_str && NULL != dest_str);
	
	start = dest_str;	
					
	while('\0' != *src_str && num_to_copy > 0)
	{
		*dest_str = *src_str; 
		++src_str;
		--num_to_copy;
		++dest_str;
	}		
	
	return start;		

}

int StrNCmp(const char *str1, const char *str2, size_t num_to_compare)
{ 
	assert(NULL != str1 && NULL != str2);
	
	while(*str1 == *str2 && '\0' != *str1  && num_to_compare > 0)
	{	
		++str1;
		++str2;	
		--num_to_compare;
	}
	
	return (int)*str1 - (int)*str2;
}
	

int StrCaseCmp(const char *str1, const char *str2)
{
	
	assert(str1 != 0 && str2 != 0);
	
	while(toupper(*str1) == toupper(*str2))
	{

		if('\0' == *str1)
		{
			return 0;
		}
		++str1;
		++str2;
		
	}
	
	return *str1 - *str2;
	
}


char *StrChr(const char *str, int ch)
{ 
	assert(NULL != str);
	
	while(ch != *str && '\0' != *str) 
	{	
		++str;
	}
	
	if(*str == ch)
	{
		return (char*)str;
	}
	
	return NULL;	
}
char *StrDup(const char *src_str)
{	
	char *duplicate = NULL;
	
	assert(NULL != src_str);
	duplicate = (char*)malloc(StrLen(src_str) + 1);
	assert(NULL != duplicate);
	
	StrCpy(duplicate, src_str);	
	
	return duplicate;

}

char *StrCat(char *dest_str, const char *src_str)
{	
	assert(NULL != src_str && NULL != src_str);
	
	StrNCat(dest_str, src_str, StrLen(src_str));	
	
	return dest_str; 
}


char *StrNCat(char *dest_str, const char *src_str, size_t num_to_cat)
{	
	char* dest_start = dest_str;
	assert(NULL != src_str && NULL != src_str);
	
	dest_str += StrLen(dest_str);
	
	while('\0' != *src_str && num_to_cat > 0) 
	{
		*dest_str = *src_str;
		++src_str;
		++dest_str;
		--num_to_cat;
	}
	
	 *dest_str = '\0';
	
	return dest_start;
}
char *StrStr(const char *haystack, const char *needle)
{ 	
	size_t needle_size = 0;
	assert(NULL != haystack && NULL != needle);
	
	needle_size = StrLen(needle);
	
	while('\0' != *(haystack + needle_size - 1))
	{
		if(StrNCmp(haystack, needle, needle_size - 1) == 0)
		{
			return (char*)haystack;
		}
		++haystack; 		
	}
	
	 
	return NULL; 	
}


size_t StrSpn(const char* src_str, const char *accept)
{
	size_t count = 0; 
	assert(NULL != src_str && NULL != accept);
	
	while(NULL != StrChr(accept, *src_str))
	{
		++count;
		++src_str;
	}
	
	return count;
}
int StrPali(const char* str)
{	
	char* start_str = NULL;
	assert(NULL != str);
	
	start_str = (char*)str;
	
	
	str += StrLen(str) - 1;
	
	while(start_str <= str)
	{
		if(*start_str != *str)
		{
			return 0;
		}
		--str;
		++start_str;
	}
	
	return 1;
}

int SevenBoom(int start, int end)
{	
	char digits[12] = "";
	
	while(start <= end) 
	{
	
		sprintf(digits,"%d", start);
		
		if(0 == (start % 7))
		{
			printf("BOOM\n");
		} 
		else if(NULL != StrChr(digits, '7'))
		{
			printf("BOOM\n");
		}
		else
		{
			printf("%d\n",start);
		}
		++start;
		
	}
	
	return 0;	
}

