#ifndef __WORDOPT_H__
#define __WORDOPT_H__

#define ALIGN sizeof(size_t)



typedef enum RESULT
{
    FAIL = -1,
    SUCCESS = 0, 
    ALIGNED 
}RESULT;   

/*
Description: Changes the string's n first characters into a given char .
arguments:
     *str - A valid void pointer.
     *c - The character that the string needs to be changed.
	*n 	 - The number of characters needs to be changed.
return: Returns the string if it succeeded.
*/
void *Memset(void *str, int c, size_t n);

/*
Description: Changes the string's n first characters into a given char .
arguments:
     *dest - A valid void pointer.
     *src - The source void that the dest pointer needs to be copied to.
	*n 	 - The number of characters needs to be copied.
return: Returns the string if it succeeded.
*/
void *Memcpy(void *dest, void *src, size_t n);

#endif
