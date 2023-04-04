#include <stdio.h>/*printf*/
#include <stdlib.h>/*malloc*/
#include <string.h>/*strlen, strcat*/
#include "Structs.h"

#define MAX2(a, b) (a >= b ? a : b)

#define MAX3(a, b, c) (MAX2(MAX2(a, b),c))

#define VAR_SIZE(VAR) ((size_t)(&(VAR)+1)-(size_t)(&(VAR)))

#define TYPE_SIZE(TYPE) ((size_t)((TYPE*)0 + 1))


int main()
{
	element_t elem[3];
	int x = 3;
	
	CreateInt(&elem[0], 4);
	CreateFloat(&elem[1], 2.65);
	CreateString(&elem[2], "Bar HaMalik");
	printf("The elements created in the element array are: \n");
	PrintAll(elem, 3);
	printf("\n");
	
	printf("After adding the number 8 to the elements: \n");
	AddAll(elem, 3, 8);
	PrintAll(elem, 3);
	printf("\n");
	
	printf("And now we clean.. \n");
	CleanUpAll(elem, 3);
	printf("\n");
	
	
	
	printf("Test for the macros we defined:\n");
	printf("The largest number between 1, 2 and 3 is %d\n", MAX3(1, 2, 3));
	printf("The size of 3 is %lu\n", VAR_SIZE(x));
	printf("The size of the struct Element is %lu\n", TYPE_SIZE(element_t));
	
	
	
	return 0;
	
}
