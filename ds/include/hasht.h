/*
Developer: BarSH
Reviewer: MaorH
Status: Approved
Date: 18.6.23
*/
#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h>/*size_t*/


/*
struct Hash_Table
{
    size_t capacity;
    size_t (*hash_func)(void *key);
    int (*compare_func)(const int *, const int*);
    dlist_t **table;
}
*/
typedef struct Hash_Table hasht_t;

/*========================================================*/
/*
Description: Creates an Hash Table.
Arguments: 
    hash_func - A valid pointer to a hashing function.
    compare_func - A valid pointer to a compare function. 
    capacity - A valid max capacity of the table. 
Return: 
    Pointer to a hash table, otherwise NULL. 
Time complexity: O(n)
Space complexity: O(n)
*/
hasht_t *HashTCreate(size_t (*hash_func)(void *key), 
                     int (*compare_func)(const void *, const void *),
                     size_t capacity);

/*========================================================*/
/*
Description: Destroys the Hash Table.
Arguments: 
    hash - A valid pointer to the hash table.
Return: 
    Void. 
Time complexity: O(n), worst case O(n^2)
Space complexity: O(1)
*/
void HashTDestroy(hasht_t *hash);

/*========================================================*/
/*
Description: Counts the number of values in the hash table.
Arguments: 
    hash - A valid pointer to the hash table.
Return: 
    The amount of the values in the hash table. 
Time complexity: O(n)
Space complexity: O(1)
*/
size_t HashTSize(const hasht_t *hash);


/*========================================================*/
/*
Description: Operate on each value in the hash table.
Arguments: 
    hash - A valid pointer to the hash table.
    call_back - A valid pointer to an operation function. 
    action_param - A valid pointer to a parameter to operate with.
Return: 
    SUCCESS if  all operations were succseful, FAIL otherwise.
Time complexity: O(n)
Space complexity: O(1)
*/
int HashTForEach(hasht_t *hash, 
                 int (*call_back)(void *in_table, void *action_param), 
                 void *action_param);

/*========================================================*/
/*
Description: Find a value in the hash table.
Arguments: 
    hash - A valid pointer to the hash table.
    key - A key to a value to look for. 
Return: 
    The value if found, NULL otherwise.
Time complexity: O(n)
Space complexity: O(1)
*/
void *HashTFind(hasht_t *hash, void *key);

/*========================================================*/
/*
Description: Find a value in the hash table.
Arguments: 
    hash - A valid pointer to the hash table.
    key - A valid key to parse.
    data - A valid data pointer to a insert. 
Return: 
    SUCCESS if succeeded, FAIL otherwise.
Time complexity: O(1), worst case O(n).
Space complexity: O(1)
*/
int HashTInsert(hasht_t * hash, void *key, void* data);

/*========================================================*/
/*
Description: Removes a value in the hash table.
Arguments: 
    hash - A valid pointer to the hash table.
    key - A valid key to remove.
Return: 
    The value if found, NULL otherwise.
Time complexity: O(1), worst case O(n).
Space complexity: O(1)
*/
void HashTRemove(hasht_t *hash, const void *key);

/*========================================================*/
/*
Description: Checks if the hash table is empty.
Arguments: 
    hash - A valid pointer to the hash table.
Return: 
    TRUE if empty, FALSE otherwise.
Time complexity: O(1)
Space complexity: O(1)
*/
int HashTIsEmpty(const hasht_t *hash);

#endif /*__HASH_H__*/
