/*
Dev: BarSH
Rev: MariaP
Status: Approved
Date: 19.4.23
*/

#include <stdio.h> /*printf*/

#define IS_LITTLE_ENDIAN (*(unsigned short *)"\0\xff" < 0x100)

void IsBigEndian();

int main()
{
	IsBigEndian();
	printf("%d\n",IS_BIG_ENDIAN);
	
	return (0);
}

void IsBigEndian()
{
	size_t check = 1;
	
	printf("%d\n", *(char*)&check);	
}


