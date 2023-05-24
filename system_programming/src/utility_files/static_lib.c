#include <stdio.h>
#include <stdlib.h>
#include "full_mapping.h"

const int global_answer = 42;
int global_warmming = 33;
static int k = 4;

static void StaticHelloWorld(void)
{
	printf("hello world\n");
}

extern int Addition(int num)
{
	num +=1;
	return num;
}

void Malloc(void)
{
	int *the_malloc = (int *)malloc(sizeof(int));
	printf("yes, this malloc!\ n");
	free(supermalloc);
	printf("game-over\n");
}

void Meh(void)
{
	const int not_easy = 1;
	const char *strliteral = "literally, string";
	int easy = 2;
	char *literal = "string";
	static int ben_el = 1;
	
}
