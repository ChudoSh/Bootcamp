/*
Developer: BarSH
Reviewer: MaorH
Status: Approved
Date: 18.6.23
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "hasht.h"
#include "dlist.h"

struct Hash_Table
{
    size_t capacity;
    size_t (*hash_func)(void *key);
    int (*compare_func)(const void *, const void *);
    dlist_t **table;
};

typedef enum STATUS
{
    SUCCESS = 0,
    FAIL = -1
}status_t;

typedef struct HASH_NODE
{
    void *value; 
    void *key;
}bucket_t;

typedef int (*is_match_t)(const void *, const void *);

typedef struct MATCHER
{
	is_match_t key_match;
	const void *key;
}matcher_t;

static status_t InitTable(dlist_t **table, size_t capacity);
static bucket_t *CreateBucket(void *data, void *key);

static dlist_t **GetTable(hasht_t *hash);
static size_t GetCapacity(hasht_t *hash);
static dlist_t *GetList(dlist_t **table, size_t index);
static size_t GetKeyed(hasht_t *hash, const void *key);
static void SetBucketValue(bucket_t *bucket, void *value);
static void SetBucketKey(bucket_t *bucket, void *key);

static int DestroyBucket(void *bucket, void *unused);
static int IsMatch(void *check, const void *check_against);

/*Creates a hash table*/
hasht_t *HashTCreate(size_t (*hash_func)(void *key), 
                     int (*compare_func)(const void *, const void *),
                     size_t capacity)
{
    hasht_t *hash = NULL;

    assert(0 < capacity);
    assert(NULL != hash_func);
    assert(NULL != compare_func);

    hash = (hasht_t *)malloc(sizeof(hasht_t));
    if (NULL == hash)
    {
       return (NULL); 
    }

    hash->table = (dlist_t **)malloc(sizeof(dlist_t *) * capacity);
    if (NULL == hash)
    {
        free(hash);
        return (NULL); 
    }

    if (FAIL == InitTable(hash->table, capacity))
    {
        free(hash->table);
        free(hash);
        return (NULL);
    }
     
    hash->capacity = capacity;
    hash->hash_func = hash_func;
    hash->compare_func = compare_func;

    return (hash);
}

/*Destroy a hash table*/
void HashTDestroy(hasht_t *hash)
{
    size_t i = 0;
    void *unused = NULL;

    assert(NULL != hash);

    HashTForEach(hash, DestroyBucket, unused);

    while (i < GetCapacity(hash))
    {
        DListDestroy(GetList(GetTable(hash), i));
        ++(i);
    }

    free(GetTable(hash));
    free(hash);
}

/*Insert a new value*/
int HashTInsert(hasht_t * hash, void *key, void* data)
{
    size_t index = 0; 
    bucket_t *bucket = NULL;
    dlist_iter_t end = NULL;

    assert(NULL != hash);
    assert(NULL != key);

    end = DListEnd(GetList(GetTable(hash), index));
    index = GetKeyed(hash, key); 

    bucket = CreateBucket(data, key);
    if (NULL == bucket)
    {
        return (FAIL);
    }

    if (end == DListPushBack(GetList(GetTable(hash), index), bucket))
    {
        free(bucket);
        return (FAIL);
    }

    return (SUCCESS);
}

/*Removes a value from the table*/
void HashTRemove(hasht_t *hash, const void *key)
{
    size_t index = 0; 
    dlist_iter_t begin = NULL;
    dlist_iter_t end = NULL;
    matcher_t param = {NULL}; 
    bucket_t *to_remove = NULL;
    dlist_iter_t find = NULL;

    assert(NULL != hash);
    assert(NULL != key);
    assert(NULL != HashTFind(hash, (void *)key));

    index = GetKeyed(hash, key); 
    begin = DListBegin(GetList(GetTable(hash), index));
    end = DListEnd(GetList(GetTable(hash), index));
    param.key_match = hash->compare_func;
    param.key = key; 

    find = DListFind(begin, end, IsMatch, &param);
    to_remove = (bucket_t *)DListGetData(find);
    free(to_remove);
    DListRemove(find);
}

/*Operates on each value in the hash*/
int HashTForEach(hasht_t *hash, 
                 int (*call_back)(void *in_table, void *action_param), 
                 void *action_param)
{
    size_t i = 0; 
    int status = SUCCESS; 
    dlist_iter_t begin = NULL;
    dlist_iter_t end = NULL;

    assert(NULL != hash);
    assert(NULL != call_back);

    while (i < GetCapacity(hash) && SUCCESS == status)
    {
        begin = DListBegin(GetList(GetTable(hash), i));
        end = DListEnd(GetList(GetTable(hash), i));
        status = DListForEach(begin, end , call_back, action_param);

        ++(i);
    }
    
    if (SUCCESS != status)
    {
        return (FAIL);
    }

    return (SUCCESS);
}

/*Finds a value for a given key */
void *HashTFind(hasht_t *hash, void *key)
{
    size_t index = 0; 
    dlist_iter_t begin = NULL;
    dlist_iter_t end = NULL;
    dlist_iter_t found = NULL;
    matcher_t param = {NULL}; 

    assert(NULL != hash);
    assert(NULL != key);

    index = GetKeyed(hash, key); 
    begin = DListBegin(GetList(GetTable(hash), index));
    end = DListEnd(GetList(GetTable(hash), index));
    param.key_match = hash->compare_func;
    param.key = key; 

    found = DListFind(begin, end, IsMatch, &param);
    if (end == found)
    {
        return (NULL);
    }

    return (((bucket_t *)DListGetData(found))->value);
}

/*Check whether the hash table is empty*/
int HashTIsEmpty(const hasht_t *hash)
{
    assert(NULL != hash);

    return (0 == HashTSize(hash));
}

/*Counts the amount of values in the hash*/
size_t HashTSize(const hasht_t *hash)
{
    size_t size = 0; 
    size_t i = 0;
    size_t capacity = 0; 
    dlist_t **table_runner = NULL;
    
    assert(NULL != hash);

    table_runner = GetTable((hasht_t *)hash);
    capacity = GetCapacity((hasht_t *)hash);

    while (i < capacity)
    {
        size += DListSize(GetList(table_runner, i));
        ++(i);
    }

    return (size);
}

/*======================Static Funcs========================*/
static status_t InitTable(dlist_t **table, size_t capacity)
{
    size_t i = 0;

    assert(NULL != table);

    while (i < capacity)
    {
        table[i] = DListCreate();
        if (NULL == table[i])
        {
            while (0 < i)
            {
                DListDestroy(table[i]);
                --(i);
            }

            DListDestroy(table[0]);
            free(table);
            return (FAIL);
        }

        ++(i);
    }

    return (SUCCESS);
}

static bucket_t *CreateBucket(void *data, void *key)
{
    bucket_t *new_bucket = NULL; 

    assert(NULL != data);
    assert(NULL != key);
    
    new_bucket = (bucket_t *)malloc(sizeof(bucket_t));
    if (NULL == new_bucket)
    {
        return (NULL);
    }

    SetBucketValue(new_bucket, data);
    SetBucketKey(new_bucket, key); 

    return (new_bucket);
}

static int DestroyBucket(void *bucket, void *unused)
{
    assert(NULL != bucket);

    (void)unused;

    free((bucket_t *)bucket);

    return (SUCCESS);
}

static dlist_t **GetTable(hasht_t *hash)
{ 
    assert(NULL != hash);

    return (hash->table);
}

static size_t GetCapacity(hasht_t *hash)
{ 
    assert(NULL != hash);

    return (hash->capacity);
}

static dlist_t *GetList(dlist_t **table, size_t index)
{ 
    assert(NULL != table);

    return (table[index]);
}

static void SetBucketValue(bucket_t *bucket, void *value)
{
    bucket->value = value;
}

static void SetBucketKey(bucket_t *bucket, void *key)
{
    bucket->key = key;
}

static size_t GetKeyed(hasht_t *hash, const void *key)
{   
    assert(NULL != hash);
    assert(NULL != key);

    return (hash->hash_func((void *)key) % GetCapacity(hash));
}

static int IsMatch(void *key, const void *param)
{
	is_match_t is_to_remove = ((matcher_t *)param)->key_match;
	const void *param_key = ((matcher_t *)param)->key;
		
	return (0 == is_to_remove(((bucket_t *)key)->key, param_key));
}

/*void PrintTable(hasht_t *hash)
{
    size_t i = 0; 
    dlist_t **runner = NULL; 
    dlist_iter_t iter = NULL;

    assert(NULL != hash);

    runner = GetTable(hash);

    while (i < GetCapacity(hash))
    {
        while (DListEnd(runner[i]) != iter && runner[i] != NULL)
        {
            printf("List :%lu, value: %s, key: %s\n", i,(char *)((bucket_t *)DListGetData(iter))->value, (char *)((bucket_t *)DListGetData(iter))->key);
        }

        ++(i);
    }
}
*/