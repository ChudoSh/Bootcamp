/*
Dev: BarSH
Rev: 
Date: .6.23
Status: 
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

#define IS_EMPTY (0)
#define FOUND (-1)
#define UNUSED(x) ((void)(x))
#define NO_CHILD (-1)


enum BOOLEAN
{
    FALSE = 0,
    TRUE = 1
};

enum STATUS
{
    FAIL = -1, 
    SUCCESS = 0   
};


struct BSTNode
{
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
    void *value;
};

struct BST
{
    bst_node_t root_stub;
    int (*compare_func)(const void *a, const void *b);
};

static int GetSize(void *a, void *b);
static bst_iter_t GetChild(bst_iter_t current, int child);
static bst_iter_t GetParent(bst_iter_t current);
static void SetChild(bst_iter_t current, bst_iter_t to_set, int child);
static void SetParent(bst_iter_t current, bst_iter_t parent);
static bst_iter_t GetRoot(const bst_t *tree);
static bst_iter_t GetFirst(const bst_t *tree);
static void SetData(bst_iter_t current, void * data);
static bst_iter_t CreateLeaf(void *data);
static int GetCompared(const bst_t *tree,  bst_iter_t where, void *param);
static int IsLeaf(const bst_iter_t where);
static int WhichChild(bst_iter_t where);


/*Plants the tree*/
bst_t *BSTCreate(int (*compare_func)(const void *a, const void *b))
{
    bst_t *tree = NULL;

    assert(NULL != compare_func);

    tree = (bst_t *)(malloc(sizeof(bst_t)));
    if (NULL == tree)
    {
        return (NULL);
    } 
    
    tree->root_stub.value = NULL;
    tree->root_stub.parent = NULL;
    tree->root_stub.children[LEFT] = NULL;
    tree->root_stub.children[RIGHT] = NULL;
    tree->compare_func = compare_func;

    return (tree);
}

/*Cuts the tree down*/
void BSTDestroy(bst_t *tree)
{
    assert(NULL != tree);

    while (!BSTIsEmpty(tree))
    {
        BSTRemove(BSTBegin(tree));        
    }

    free(tree);
}

/*Grows a new leaf*/
bst_iter_t BSTInsert(bst_t *tree, void *data)
{
    bst_iter_t iter = NULL; 
    bst_iter_t insert = NULL;
    int direction = 0;  

    assert(NULL != tree);

    insert = CreateLeaf(data);
    if (NULL == insert)
    {
        return (NULL);
    }
    
    if (BSTIsEmpty(tree))
    {
        SetChild(GetRoot(tree), insert, LEFT);
        SetData(insert, data);
        SetParent(insert, GetRoot(tree));

        return (insert);
    }

    iter = GetFirst(tree);
    SetData(insert, data);
    direction = GetCompared(tree, iter, data); 

    while (FOUND != GetCompared(tree, iter, data) && (!IsLeaf(iter)))   
    {
        iter = GetChild(iter, direction); 
        direction = GetCompared(tree, iter, data);     
    }

    SetParent(insert, iter);
    SetChild(iter, insert, direction);

    return (insert);
}

/*Cuts a leaf*/
void BSTRemove(bst_iter_t current)
{ 
    bst_iter_t next = NULL; 
    bst_iter_t parent = NULL;
    int child_current = NO_CHILD;
    int child_parent = NO_CHILD;

    assert(NULL != current);

    parent = GetParent(current);

    if (current == GetChild(parent, LEFT))
    {
        child_parent = LEFT; 
    }
    else
    {
       child_parent = RIGHT; 
    }

    /*When no children*/
    if (IsLeaf(current))
    {
        if (child_parent == LEFT)
        {
            SetChild(parent, NULL, LEFT);  
        }
        
        else
        {
            SetChild(parent, NULL, RIGHT);
        } 
    }
    
    else if (NULL == GetChild(current, RIGHT) || 
             NULL == GetChild(current, LEFT))
    {
        child_current = WhichChild(current);

        /*When there is one child*/
        SetChild(parent, GetChild(current, child_current), child_parent);
        SetParent(GetChild(current, child_current), parent);          
    }

    /*When there are two kids*/
    else
    {
        next = BSTNext(current);

        SetParent(next, parent);
        SetChild(parent, NULL, RIGHT);

        SetChild(next, GetChild(current, RIGHT), RIGHT);
        SetChild(next, GetChild(current, LEFT), LEFT);

        SetParent(GetChild(current, RIGHT) ,next);
        SetParent(GetChild(current, LEFT) ,next);
    }
    
    free(current);   
}

/*Moves the monkey to the a higher branch*/
bst_iter_t BSTNext(bst_iter_t current)
{
    bst_iter_t next = NULL; 

    assert(NULL != current);

    next = current;

    if (NULL != GetChild(next, RIGHT))
    {
        next = GetChild(next, RIGHT);

        while (NULL != GetChild(next, LEFT))
        {
            next = GetChild(next, LEFT);       
        }       
    }

    else 
    {    
        next = GetParent(next);

        while (next != GetChild(GetParent(next), LEFT) && 
               NULL != GetParent(GetParent(next)))
        { 
            next = GetParent(next);
        } 

        next = GetParent(next);
    }

    return (next);
}

/*Moves the monkey to the a lower branch*/
bst_iter_t BSTPrev(bst_iter_t current)
{
    bst_iter_t prev = NULL; 

    assert(NULL != current);

    prev = current;
    if (NULL == GetParent(GetParent(prev)))
    {
        return (prev);
    }
     
    if (NULL != GetChild(prev, LEFT))
    {
        prev = GetChild(prev, LEFT);

        while (NULL != GetChild(prev, RIGHT))
        { 
            prev = GetChild(prev, RIGHT);       
        }  
    }

    else 
    {    
        prev = GetParent(prev);

        while (prev != GetChild(GetParent(prev), RIGHT) && 
               NULL != GetParent(GetParent(prev)))
        {
            prev = GetParent(prev);
        } 
    }

    return (prev);
    
}

/*Counts the many leaves the tree has*/
size_t BSTSize(const bst_t *tree)
{   
    size_t size = 0;

    assert(NULL != tree);

    BSTForEach(BSTBegin(tree), BSTEnd(tree), GetSize, &size);

    return (size);
}

/*Shows the leaf*/
void *BSTGetData(bst_iter_t where)
{
    assert(NULL != where);

    return (where->value);
}

/*Gets the lowest leaf*/
bst_iter_t BSTBegin(const bst_t *tree)
{
   bst_iter_t begin = NULL;

    assert(NULL != tree);

    begin = GetRoot(tree);

    while (NULL != GetChild(begin, LEFT))
    {
        begin = GetChild(begin, LEFT);
    }

    return (begin);
}

/*Gets the chunkiest leaf*/
bst_iter_t BSTEnd(const bst_t *tree)
{
    assert(NULL != tree);

    return (GetRoot(tree));
}

/*checks if it is winter*/
int BSTIsEmpty(const bst_t *tree)
{
    assert(NULL != tree);

    return (GetRoot(tree) == BSTBegin(tree));
}

/*Looks for a particular leaf*/
bst_iter_t BSTFind(bst_t *tree, const void *param)
{   
    bst_iter_t iter = NULL; 

    assert(NULL != tree);
    if(BSTIsEmpty(tree))
    {
        return (BSTEnd(tree));
    }

    iter = GetFirst(tree);

    while (!IsLeaf(iter) && FOUND != GetCompared(tree, iter, (void *)param))
	{
        iter = GetChild(iter, GetCompared(tree, iter, (void *)param));      
	}

    if (FOUND == GetCompared(tree, iter, (void *)param))
    {
        return (iter);
    }
    
	return (BSTEnd(tree));
}

/*Does something to all leaves*/
int BSTForEach(bst_iter_t from, bst_iter_t to, 
               int (*call_back)(void *, void *), void *param)
{
    int status = 0;
    
	assert(NULL != call_back);
	
	while (from != to)
	{
		status = call_back(BSTGetData(from), param); 
		
		if (SUCCESS != status)
		{
			return (status);
		}
		
		from = BSTNext(from);
	}
	
	return (TRUE);
}

/*Checks if two monkeys are equal*/
int BSTIsSameIter(const bst_iter_t iter1, const bst_iter_t iter2)
{
    assert(NULL != iter1);
    assert(NULL != iter1);

    return (iter1 == iter2);
}



/**********************static functions****************************/
static bst_iter_t CreateLeaf(void *data)
{  
    bst_iter_t new_leaf = (bst_iter_t)(malloc(sizeof(bst_node_t)));
    if (NULL == new_leaf)
    {
        return (NULL);
    }

    SetParent(new_leaf, NULL);
    SetChild(new_leaf, NULL, RIGHT);
    SetChild(new_leaf, NULL, LEFT);
    SetData(new_leaf, data);

    return (new_leaf);
}

static int GetSize(void *a, void *b)
{
	++(*(size_t *)b);
	
	UNUSED(a);
	
	return (SUCCESS);		
}

static bst_iter_t GetChild(bst_iter_t current, int child)
{
    return (current->children[child]);    
}

static bst_iter_t GetParent(bst_iter_t current)
{
    return (current->parent);    
}

static void SetChild(bst_iter_t current, bst_iter_t to_set, int child)
{
    current->children[child] = to_set;   
}

static void SetParent(bst_iter_t current, bst_iter_t parent)
{
    current->parent = parent;   
}

static void SetData(bst_iter_t current, void * data)
{
    current->value = data;   
}

static bst_iter_t GetFirst(const bst_t *tree)
{
    return (GetChild(GetRoot(tree), LEFT));    
}

static bst_iter_t GetRoot(const bst_t *tree)
{
    bst_iter_t root = NULL; 

    root = &(((bst_t *)tree)->root_stub);

    return (root);    
}

static int GetCompared(const bst_t *tree,  bst_iter_t where, void *param)
{
    int status = 0; 

    assert(NULL != tree);
    
    status = tree->compare_func(BSTGetData(where), param);

    if (0 < status)
    {
        return (LEFT);
    }

    else if (0 > status)
    {
        return (RIGHT);
    }

    return (FOUND);
}

static int IsLeaf(const bst_iter_t where)
{
    return (NULL == GetChild(where, RIGHT) && NULL == GetChild(where, LEFT));
}

static int WhichChild(bst_iter_t where)
{ 
    assert(NULL != where);

    if (NULL != GetChild(where, LEFT))
    {
        return (LEFT);
    }

    else if (NULL != GetChild(where, RIGHT))
    {
        return (RIGHT);
    }

    return (NO_CHILD);
}


