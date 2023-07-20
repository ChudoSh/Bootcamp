/*
Dev:BarSh
Rev:
Status:
Date:
*/

#include <stdio.h>
#include <string.h>

#include "../include/watchdog.h"

int main()
{
    int i = 0; 
    char *path = "watchdog_test.c";
    printf("WD Init\n");
    WDStart(&path);
    for (i = 0; i < 10; ++i)
    {
		printf("%d bark\n", i + 1);
        sleep(1);
    }
    WDStop(10);

    return (0);
}





