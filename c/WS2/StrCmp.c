/* 
Dev: BarSH
Rev: EtaiSH
Staus: Not Rev Yet
Date: 19.3.23
*/

#include <stdio.h>
#include <assert.h>


size_t StrCmp(const char *str1, const char *str2);


int main()
{
	char str1[] = "Banana";
	char str2[] = "";
	
	printf("%ld\n",StrCmp(str1,str2));
	
	return 0; 
}

size_t StrCmp(const char *str1, const char *str2)
{
	assert(str1 != 0 || str2 != 0);
	
	while(*str1 != '\0' && *str2 != '\0')
	{
	
		if(*str1 - *str2 > 0 && *str2 == '\0')
		{
			return 1;
		}
		
		if(*str1 - *str2 < 0 && *str1 == '\0')
		{
			return -1; 	
		}
		
		++str1;
		++str2;
	}
	
	return 0;
}

