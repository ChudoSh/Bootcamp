#include <stdio.h>
#include <stdlib.h>


int x = 2;
const int const_glob =  3;

static void stat_func()
{
}

extern void extrn_func()
{
}

void PrintAddress()
{
	const int const_int = 20;
	const static int const_stat_int = 20;  
    const char *str_const = "FullMemory const";	
	
	char *heapvar_const = (char *)malloc(sizeof(char));
	char *heapvar = (char *)malloc(sizeof(char));
	
	int i = 20;
	static int j = 20; 
    char *str = "FullMemory";
    
    printf("The address of non const global var x is %p\n", &x);
    printf("The address of glob_const is %p\n", &const_glob);
	printf("The address of stat_func is %p\n", &stat_func);
	printf("The address of extrn_func is %p\n", &extrn_func);
	printf("The address of i_const is %p\n", &const_int);
	printf("The address of const_stat_int is %p\n", &const_stat_int);
	printf("The address of str_const is %p\n", str_const);
	printf("The address of heapvar_const is %p\n", heapvar_const);
	printf("The address of heapvar is %p\n", heapvar);
	printf("The address of i is %p\n", &i);
	printf("The address of j is %p\n", &j);
	printf("The address of str is %p\n", str);
	
}

