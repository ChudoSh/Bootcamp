#include <assert.h>/*assert*/
#include <stdlib.h> /*exit*/ 
#include <stdio.h> /*printf*/
#include <string.h>/*memset*/

#define IS_LITTLE_ENDIAN (*(unsigned short *)"\0\xff" < 0x100)

void IsBigEndian();

int main()
{
	IsBigEndian();
	printf("%d\n",IS_BIG_ENDIAN);
	
	return 0;
}

void IsBigEndian()
{
	size_t check = 1;
	
	printf("%d\n", *(char*)&check);	
}


