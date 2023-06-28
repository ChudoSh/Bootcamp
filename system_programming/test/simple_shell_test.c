/*
Dev: BarSh
Rev:
Status:
Date: 28.6.23
*/

#include "simple_shell.h"

#include <stdio.h>

static void Test(int val, const char *func, int line);

int main()
{

    Test(0 == CreateProcess(), "System & Fork", __LINE__);
    
    return (0);
}

static void Test(int val, const char *func, int line)
{
	char str2[47];
	char temp[17] = {'\0'};
	sprintf(temp, " %d       ", line);
	strncpy(str2, temp, strlen(temp));
	sprintf(temp, "         ");
	sprintf(temp, " %s               ", func);
	strncpy(&str2[6], temp, strlen(temp));
	
	if (val)
	{
		strcpy(&str2[23], "\033[1;32msuccess\033[0m");
	}
	else
	{
		strcpy(&str2[23], "\033[1;31mfail\033[0m");
	}
	
	printf("%s\n", str2);
}
