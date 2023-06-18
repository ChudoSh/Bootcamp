/*
Dev: BarSH
Rev: 
Status: 
Date: 
*/

#include <string.h>
#include <stdio.h>

#include "calculator.h"

static void Test(int val, const char *func, int line);
static void TestPlusMinus();

int main()
{
    TestPlusMinus();

    return (0);
}

static void TestPlusMinus()
{
    double result = 0; 
    const char *expresssion = "1+1+1";

    Calculator(expresssion, &result);

    Test(3 == result, "Calculator", __LINE__);
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
	
	if(val)
	{
		strcpy(&str2[23], "\033[1;32msuccess\033[0m");
	}
	else
	{
		strcpy(&str2[23], "\033[1;31mfail\033[0m");
	}
	
	printf("%s\n", str2);
}
