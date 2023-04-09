#ifndef __STRING_H__
#define __STRING_H__

/*Part 1 Functions WS1*/

/************/
int StrCmp(const char *str1, const char *str2); /*Compares string*/

/********/
size_t StrLen(const char *str);/*Length of a string*/



/* Part 2 Functions Ws2*/

char *StrCpy(char *dest_str, const char* src_str);/* Copeis a string to a destination string*/

/*********/
char  *StrNCpy(char *dest_str, const char* str_src, size_t num_to_copy);/*Copies a tring by an N size*/

/*******/
int StrNCmp(const char *str1, const char *str2, size_t num_to_compare); /*Compares string by N size*/

/*****/
int StrCaseCmp(const char *str1, const char *str2);/*Compares strings while ignoring capital cases*/

char *StrChr(const char *str, int ch); /* Returns the address of the first appearance of ch*/

char *StrDup(const char *src_str);/*Duplicates a string*/

char *StrCat(char *dest_str, const char *src_str);

char *StrNCat(char *dest_str, const char *src_str, size_t num_to_cat);

char *StrStr(const char *haystack, const char *needle);

size_t StrSpn(const char* src_str, const char *accept);

int StrPali(const char* str);

int SevenBoom(int start, int end);

#endif

