#ifndef __WORDOPT_H__
#define __WORDOPT_H__

#define WORD (sizeof(size_t))
#define IS_ALIGNED(p) ((size_t)p % WORD)



typedef enum RESULT
{
    FAIL = -1,
    SUCCESS = 0 
}RESULT;   

/*
Description: Changes the string's n first characters into a given char.
arguments:
     *str - A valid void pointer.
     *c - The character that the string needs to be changed.
	*n 	 - The number of characters needs to be changed.
return: Returns the string if it succeeded.
*/
void *Memset(void *str, int c, size_t n);

/*
Description: Copies non-overlapping source pointer to a dest pointer (strings) by n characters.
arguments:
     *dest - A valid void pointer.
     *src - A valid source void pointer, not over lapping with the dest pointer.
	*n 	 - The number of characters needs to be copied.
return: Returns the string if it succeeded.
*/
void *Memcpy(void *dest, void *src, size_t n);

/*
Description: Copies any source pointer to any dest pointer (strings) by n characters.
arguments:
     *dest - A valid destination void pointer.
     *src - A valid source void pointer.
	*n 	 - The number of characters needs to be copied.
return: Returns the string if it succeeded.
*/
void *Memmove(void *dest, void *src, size_t n);

#endif
