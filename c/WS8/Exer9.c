#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*strlen, strcat*/
#include "Structs.h"


void foo2()
{
	static int g6 = 0;
	static int g7 = 7;
	void *p = malloc(10);
	free(p); p = 0;
}



static void foo1()
{
	static int g5;
	int l1 = 9;
}



int main()
{
	int g1;
	static int g2;
	static int g3 = 0;
	static int g4 = 8;

}
