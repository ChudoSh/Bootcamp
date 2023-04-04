#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#define TRUE 1
#define FAIL 0
#define UNUSED(x) (void)(x)

typedef struct Element element_t;

typedef int (*Adder)(element_t *element, int num_to_add);
typedef void (*Printer)(element_t *element);
typedef void (*Cleaner)(element_t *element);


struct Element
{
	void *val;
	Adder add;
	Printer print;
	Cleaner clean;
};


/*
Description: Initalize an Element of type Int.
arguments:
	*element - A valid address of Element.		
	*num 	 - The value the element will be initalized with.
return: always sucsses.
*/
int CreateInt(element_t *element, int num);

/*
Description: Initalize an Element of type float.
arguments:
	*element - A valid address of Element.	
	*num 	 - The value the element will be initalized with.
return: always sucsses.
*/
int CreateFloat(element_t *element, float num);

/*
Description: Initalize an Element of type string.
arguments:
	*element - A valid address of Element.	
	*num 	 - The value the element will be initalized with.
return: Returns 1 if it succeeded and 0 if it Failed.
*/
int CreateString(element_t *element, char *str);

/*
Description: Adds a given value to every Element in the element arr. Each Addition will be based on type.
arguments:
	*arr 	- A valid array of Element.
	*size 	- A valid size of the array. Invalid size larger then the array's size is undefined.
	num 	 - number to be added.
return: Returns 1 if it succeeded and 0 if it Failed.
*/
void AddAll(element_t *arr, size_t size, int num);

/*
Description: Frees all allocated memory used by Elements within the array.
arguments:
	*arr 	- A valid array of Element.
	*size 	- A valid size of the array. Invalid size larger then the array's size is undefined.
return: void.
*/
void CleanUpAll(element_t *arr, size_t size);

/*
Description: Prints all Elements in the array.
arguments:
	*arr 	- A valid array of Element.
	*size 	- A valid size of the array.
return: void.
*/
void PrintAll(element_t *arr, size_t size);

#endif /*__STRUCTS_H__*/





