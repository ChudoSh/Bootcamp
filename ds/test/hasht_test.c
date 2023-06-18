/*
Developer: BarSH
Reviewer: MaorH
Status: Approved
Date: 18.6.23
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "hasht.h"

static void TestCreatenDestroy();
static void TestInsertSize();
static void TestFindRemove();
static void TestDictionary();
static int Compare(const void *a, const void *b);
static size_t HashFunc(void *key);
static size_t HashFuncDic(void *key);
static void AutomatedTest(int val, const char *func, int line);

int main()
{
    TestCreatenDestroy();
    TestInsertSize();
    TestFindRemove();
    TestDictionary();

    return (0);
}


static void TestCreatenDestroy()
{
    hasht_t *hash = HashTCreate(HashFunc ,Compare, 5);

    AutomatedTest(HashTIsEmpty(hash), "Create & IsEmpty", __LINE__);
    
    HashTDestroy(hash);
}

static void TestInsertSize()
{
    size_t i = 0;
    char *value[5] = {"Bar", "Etai", "Maria","Ido", "Eylon"};
    char *keys[5] = {"Shadkhin", "Shimoni", "Ponomariov","Issac", "Enache"};
    hasht_t *hash = HashTCreate(HashFunc ,Compare, 5);

    for(i = 0; i < 5; ++i)
    { 
        HashTInsert(hash, keys[i], value[i]);
    } 

    /*PrintTable(hash);*/

    AutomatedTest(5 == HashTSize(hash), "Insert & Size", __LINE__);

    HashTDestroy(hash);

}

static void TestFindRemove()
{
    size_t i = 0;
    char *value[5] = {"Bar", "Etai", "Maria","Ido", "Eylon"};
    char *keys[5] = {"Shadkhin", "Shimoni", "Ponomariov","Issac", "Enache"};
    hasht_t *hash = HashTCreate(HashFunc ,Compare, 5);

    for(i = 0; i < 5; ++i)
    { 
        HashTInsert(hash, keys[i], value[i]);
    } 

    HashTRemove(hash, "Shimoni");

    AutomatedTest(NULL == HashTFind(hash, "Shimoni"), "Remove", __LINE__);
    AutomatedTest(value[2] == HashTFind(hash, "Ponomariov"), "Find", __LINE__);

    HashTDestroy(hash);

}

static void TestDictionary()
{
    hasht_t *table = HashTCreate(HashFuncDic, Compare, 200000);
	FILE *fp = NULL;
	int exists = 1;
	size_t i = 0;
	char buffer[200000][40];
    char scan[40];
    

	fp = fopen("/usr/share/dict/words", "r");
	if (NULL == fp)
	{
        AutomatedTest(NULL == fp, "Open", __LINE__);
		return;
	}

    while (fgets(buffer[i], 40, fp) && i < 200000)
	{
		HashTInsert(table, buffer[i], &exists);
		++i;
	}

    if (0 != fclose(fp))
	{
		AutomatedTest(0 != fclose(fp), "Close", __LINE__);
		return;
	}

	scanf("%s", scan);
	strcat(scan,"\n");
	if (NULL == HashTFind(table, scan))
	{
		AutomatedTest(0, "Scan Not Found", __LINE__);
		return;
	}

	AutomatedTest(1, "Dictionary & Scan", __LINE__);

    HashTDestroy(table);

}


static int Compare(const void *a, const void *b)
{   
    return (strcmp((char *)a, (char *)b));
}

static size_t HashFunc(void *key)
{
    char *str = NULL;
    size_t converted_key = 0; 

    assert(NULL != key);

    str = (char *)key;

    while ('\0' != *str)
    {
        converted_key += *str; 
        ++(str);
    }

    return (converted_key);
}

static size_t HashFuncDic(void *key)
{
    char *str = key;
	size_t index = 0;
	int factor = 31;
	int cap = 200000;
	long int p_pow = 1;

	while ('\0' != *(char *)str)
	{
		index = (index + ((*(char *)str - 'a' + 1) * p_pow)) % cap;
		++(str);
		p_pow = (p_pow * factor) % cap;
	}

	return (index);

}

static void AutomatedTest(int val, const char *func, int line)
{
	char str2[47];
	char temp[100] = {'\0'};
	sprintf(temp, " %d       ", line);
	strncpy(str2, temp, strlen(temp));
	sprintf(temp, "         ");
	sprintf(temp, " %s               ", func);
	strncpy(&str2[6], temp, strlen(temp));
	
	if (val)
	{
		strcpy(&str2[23], "\033[1;32msuccess\033[0m");
	}
	else
	{
		strcpy(&str2[23], "\033[1;31mfail\033[0m");
	}
	
	printf("%s\n", str2);
}

