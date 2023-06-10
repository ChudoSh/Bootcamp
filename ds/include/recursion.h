#ifndef __RECURSION_H__
#define __RECURSION_H__

#include "stack.h"

typedef struct node
{
	void *data;
	struct node *next;
}node_t;

/***********************************************************************/
/*
Description: Calculated the n number in the Fibonnaci sequence.
Arguments: 
	element_index : An index to be calculated to.
Return: 
	The number in the n position in the Fibonnaci sequence.
Time complexity: O(n).
Space complexity: O(1).
*/
int Fibonnachi(int element_index);

/***********************************************************************/
/*
Description: Flips a given list.
Arguments: 
	head : The head of the list.
Return: 
	The new head of the list.
Time complexity: O(n).
Space complexity: O(1).
*/
node_t *Flip(node_t *head);

/***********************************************************************/
/*
Description: Sorts a given stack.
Arguments: 
	stack : A valid pointer to a stack.
	capacity : The capacity of the given stack.
Return: 
	A new sorted stack pointer.
Time complexity: O(n).
Space complexity: O(1).
*/
stack_t *SortStack(stack_t *unsorted, size_t capacity);

/***********************************************************************/
/*
Description: Calculates the length of a given string.
Arguments: 
	str : A valid string.
Return: 
	The length of the string.
Time complexity: O(n).
Space complexity: O(1).
*/
size_t Strlen(char *str);

/***********************************************************************/
/*
Description: Compares two strings.
Arguments: 
	dest : A valid string.
	src : A valid string.
Return: 
	0 if they are equal, a positive number if det is bigger, 
		negative number otherwise. 
Time complexity: O(n).
Space complexity: O(1).
*/
size_t Strcmp(char *dest, char *src);


/***********************************************************************/
/*
Description: Copies a string to another.
Arguments: 
	dest : A valid string.
	src : A valid string.
Return: 
	The copied string 
Time complexity: O(n).
Space complexity: O(1).
*/
char *Strcpy(char *dest, char *src);

/***********************************************************************/
/*
Description: Concatecates a string to another.
Arguments: 
	dest : A valid string.
	src : A valid string.
Return: 
	The concatecated string 
Time complexity: O(n).
Space complexity: O(1).
*/
char *Strcat(char *dest, char *src);


#endif /*__RECURSION_H__*/