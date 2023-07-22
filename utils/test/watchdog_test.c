/*
Dev:BarSh
Rev:
Status:utils/test/watchdog_test.cB
Date:
*/

#include <stdio.h>
#include <string.h>

#include "../include/watchdog.h"

int main(int argc, char *argv[])
{
    char *path = "/home/barchik/Mygit/bar.shadkhin/utils/test/watchdog_test.out";
    int i = 0; 
    printf("Starting Program\n");
    WDStart(&path);
    for (i = 0; i < 20; ++i)
    {
		printf("%d bark\n", i + 1);
        sleep(1);
    }
    WDStop(10);

    return (0);
    (void)argc;
    (void)argv;
}