/*
Rev: EtaiSh
Dev: BarSh
status: Approved
date: 2.7.23
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knightstour.h"

static void AutoTest(int val, const char *func, int line);
static void Test();

int main()
{
	Test();
	return (0);
}

static void Test()
{   
	status_t status = 0;
    int i = 0;
    unsigned char Path[64] = {'\0'};
	status = KnightsTour(0,0, 5,  0, Path);

	printf("%d\n", status);

    AutoTest(KNIGHT_TOUR_SUCCESS == status , "Bruth Force", __LINE__);
    
    for (i = 0; i < 64; ++i) 
    {
        printf("%d\n", Path[i]);
    }
    
}

static void AutoTest(int val, const char *func, int line)
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
