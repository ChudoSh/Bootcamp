/*******

Dev: BarSH
Rev: DanielHA
Status: Approved
Date: 26.3.23

*/
#include <assert.h>/*assert()*/
#include <stddef.h>/*size_t*/
#include <stdlib.h>/*malloc()*/
#include <ctype.h> /*tolower*/
#include <stdio.h> /*printf*/
#include <string.h> /*strlen*/

#define STOP -1


void Free2DP(char **arr, size_t size);
char *StrDup(const char *src_str);
size_t GetSizePP(char **arr);
size_t GetSizePP(char **arr);
char *SetLower(char *arr);
char **LowStr(char **dest, char **src);

extern char** environ;

int main()
{	

	size_t i = 0; 
 	 
	char **buffer  = NULL;	
	char **bufferpt = NULL; 
	size_t envsize = GetSizePP(environ);
	
	buffer = (char**)malloc(sizeof(char*) * envsize);	
	bufferpt = buffer; 
	
	if(NULL == buffer)
	{
		return STOP; 
	}
	
	if(NULL == LowStr(buffer,environ))
	{
		free(buffer); 
		return STOP; 
	}	
	for(i = 0; i < envsize; ++i)
	{
		printf("%s\n", *bufferpt);
		++bufferpt;
			
	}
  	
  	Free2DP(buffer, envsize);  
  	free(buffer);
  	buffer = NULL;
  	  
 	return 0;
}

void Free2DP(char **arr, size_t size)
{
	if(NULL == arr)
	{
		return; 
	}
	
	while(size > 0)
	{
		free(*arr);	
		++arr;
		--size; 
	}
	
}
char *StrDup(const char *src_str)
{	
	char *duplicate = NULL;
	
	duplicate = (char*)malloc(strlen(src_str) + 1);
	
	if(NULL == duplicate)
	{
		return NULL;
	}
	
	strcpy(duplicate, src_str);	
	
	return duplicate;

}
size_t GetSizePP(char **arr)
{
	size_t size = 0;

	if(NULL == arr)
	{
		return 0;
	}
	
	while(NULL != *arr)
	{
		++size;
		++arr;
	}
	
	return size;
}



char *SetLower(char *arr)
{
	char *start = NULL;
	
	if(NULL == arr)
	{
		return NULL;
	}

	start = arr;
	
	while('\0' != *arr)
	{
		*arr = tolower(*arr);
		++arr;
	}
	
	return start;
}


char **LowStr(char **dest, char **src)
{
	char **start = NULL; 
	
	if(NULL == src && NULL == dest)
	{
		return NULL;
	}
	
	start = dest;
	
	while(NULL != *src)
	{
		*dest = StrDup(*src);
		
		if(NULL == src && NULL == dest)
		{
			Free2DP(dest, (size_t)((dest - start) / sizeof(*start)));
			return NULL;
		}
		
		SetLower(*dest);
		++dest;
		++src;
	
	}
	
	return start;
}




