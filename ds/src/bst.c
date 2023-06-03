/*
Dev: BarSH
Rev: 
Date: .6.23
Status: 
*/

#include <assert.h>
#include <stdlib.h>

#include "bst.h"

#define IS_EMPTY (0)
#define FOUND (-1)
#define UNUSED(x) ((void)(x))

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
static bst_iter_t CreateLeaf();
static int GetCompared(const bst_t *tree,  bst_iter_t where, void *param);


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
    
    SetParent(GetRoot(tree), NULL);
    SetChild(GetRoot(tree), NULL, RIGHT);
    SetChild(GetRoot(tree), NULL, LEFT);
    SetData(GetRoot(tree), NULL);

    tree->compare_func = compare_func;

    return (tree);
}

/*Cuts the tree down*/
void BSTDestroy(bst_t *tree)
{
    assert(NULL != tree);

    while (NULL != GetFirst(tree) && BSTBegin(tree) == BSTEnd(tree))
    {
        BSTRemove(BSTBegin(tree));        
    }

    free(tree);
}

/*Grows a new leaf*/
bst_iter_t BSTInsert(bst_t *tree, void *data)
{
    bst_iter_t insert = NULL;
    int direction = 0;  

    assert(NULL != tree);
    if (BSTEnd(tree) == BSTFind(tree, data))
    {
        return (NULL);
    }

    insert = CreateLeaf();
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

    insert = GetFirst(tree);

    while (NULL != GetChild(insert, RIGHT) && NULL != GetChild(insert, LEFT))
    {
        direction = GetCompared(tree, insert, data);
        insert = GetChild(insert, direction);
    }

    insert 

    return (insert);
}

/*Cuts a leaf*/
void BSTRemove(bst_iter_t current)
{
    assert(NULL != current);
    assert(NULL != GetParent(current));

    if (NULL ==  GetChild(current, LEFT) && NULL ==  GetChild(current, RIGHT))
    {
        if (GetChild(GetParent(current), LEFT) == current)
        {
            SetChild(GetParent(current), NULL, LEFT);
        }
        
        else
        {
            SetChild(GetParent(current), NULL, RIGHT);
        }

        free(current);
        return;      
    }
    
    else if
    {
        SetParent(BSTPrev(current), GetParent(current));
        SetChild(GetParent(BSTPrev(current)), NULL, RIGHT);

        SetChild(BSTPrev(current), GetChild(current, RIGHT), RIGHT);
        SetChild(BSTPrev(current), GetChild(current, LEFT), LEFT);

        SetParent(GetChild(current, RIGHT) ,BSTPrev(current));
        SetParent(GetChild(current, LEFT) ,BSTPrev(current));  
    }

    free(current);     
}

/*Moves the monkey to the a higher branch*/
bst_iter_t BSTNext(bst_iter_t current)
{
    bst_iter_t next = NULL; 

    assert(NULL != current);
    assert(NULL != current->parent);

    next = current;

    if (NULL == GetChild(next, RIGHT) && NULL == GetChild(next, LEFT))
    {
        while (next != GetChild(GetParent(next), LEFT) 
               && NULL != GetParent(next))
        {
            next = GetParent(next);
        }       
    }

    else 
    {    
        while (NULL !=  GetChild(next, LEFT) && NULL != GetChild(next, RIGHT))
        { 
            if (NULL == GetChild(next, LEFT))
            {
                next = GetChild(next, RIGHT);
            }

            next = GetChild(next, LEFT);
        } 

    }

    return (next);
}

/*Moves the monkey to the a lower branch*/
bst_iter_t BSTPrev(bst_iter_t current)
{
    bst_iter_t prev = NULL; 

    assert(NULL != current);
    assert(NULL != GetParent(current));

    prev = current; 

    if (NULL == GetChild(prev, RIGHT) && NULL == GetChild(prev, LEFT))
    {
        while (prev != GetChild(GetParent(prev), RIGHT) 
               && NULL != GetParent(prev))
        {
            prev = GetParent(prev);
        }       
    }

    else 
    {    
        while (NULL != GetChild(prev, LEFT) && NULL != GetChild(prev, RIGHT))
        { 
            if (NULL == GetChild(prev, RIGHT))
            {
                prev = GetChild(prev, LEFT);
            }

            prev = GetChild(prev, RIGHT);
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

    begin = GetFirst(tree);

    while (NULL != begin && NULL != GetChild(begin, LEFT))
    {
        begin = GetChild(begin, LEFT);
    }

    return (begin);
}

/*Gets the chunkiest leaf*/
bst_iter_t BSTEnd(const bst_t *tree)
{
    bst_iter_t end = NULL;

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

    iter = GetFirst(tree);

    while (NULL != iter && FOUND != GetCompared(tree, iter, (void *)param))
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
	
	while (from != to && NULL != from)
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
static bst_iter_t CreateLeaf()
{  
    bst_iter_t new_leaf = (bst_iter_t)(malloc(sizeof(bst_node_t)));
    if (NULL == new_leaf)
    {
        return (NULL);
    }

    SetParent(new_leaf, NULL);
    SetChild(new_leaf, NULL, RIGHT);
    SetChild(new_leaf, NULL, LEFT);
    SetData(new_leaf, NULL);

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

static void SetChild(bst_iter_t current, bst_iter_t to_set,  int child)
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
    assert(NULL != where);
    
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


