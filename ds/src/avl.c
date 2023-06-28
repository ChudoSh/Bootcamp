/*
Developer:BarSH
Reviewer:MariaP
status: Approved
date: 18/06/23
*/

#include <stdlib.h>/*malloc*/
#include <assert.h>/*assert*/
#include <sys/types.h> /*ssize_t*/

#include "avl.h"

#define FOUND (-1)

enum CHILDREN
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN
};

enum RESULT
{
    FAIL = -1, 
    SUCCESS = 0
};
    
enum MAGIC_NUMS
{
    IS_EMPTY = 0,
    LEAF_HEIGHT = 1,
    PARENT_HEIGHT = 2, 
    NO_CHILD = -1
};

enum ROTATIONS
{
    LOWER_BALANCE = -1,
    UPPER_BALANCE = 1
};


struct AVL_NODE
{
    avl_node_t *children[NUM_OF_CHILDREN];
    void *data;
    size_t node_level;
};

struct AVL
{
    avl_node_t *root;
    int (*compare_func)(const void *, const void *);
};

static avl_node_t *GetChild(avl_node_t *node, int child);
/*static avl_node_t *GetRoot(avl_tree_t *tree);*/
/*void *GetData(avl_node_t *tree);*/
static size_t GetHeight(avl_node_t *node);

static int IsLeaf(avl_node_t *where);
static int GetCompared(avl_tree_t *tree, void *to_check ,void *check_against);
static int GetSize(void *a, void *b);


static void SetChild(avl_node_t *node, avl_node_t *new_child ,int child);
static void SetData(avl_node_t *node, void *new_data);
static void SetHeight(avl_node_t *node, size_t new_level);
static void SetNewNode(avl_tree_t *tree, avl_node_t *node);

static avl_node_t *CreateLeaf(void *data);

/*int RecInsert(avl_tree_t *tree ,avl_node_t *where, avl_node_t *insert);*/
avl_node_t *RecRemove(avl_tree_t *tree, avl_node_t *to_remove, void *data);
static void DestroyNode(avl_node_t *to_free);

static int TraversePre(avl_node_t *where, 
                       int (*call_back)(void *, void *), void *param);
static int TraverseIn(avl_node_t *where, 
                       int (*call_back)(void *, void *), void *param);
static int TraversePost(avl_node_t *where, 
                       int (*call_back)(void *, void *), void *param);
static void *FindValue(avl_tree_t *tree,avl_node_t *where, const void *param);
static avl_node_t *TravesreDir(avl_node_t *where, int direction);


static int IsHeigher(avl_node_t *check, avl_node_t *check_against);
static int ToBalance(avl_node_t *current);
static avl_node_t *RotateLeft(avl_tree_t *tree, avl_node_t *current);
static avl_node_t *RotateRight(avl_tree_t *tree, avl_node_t *current);

static avl_node_t *BalancedInsert(avl_tree_t *tree, avl_node_t *where, 
                                  avl_node_t *insert);
 
/*====================Main Funcs==============================================*/

/*Creates a tree*/
avl_tree_t *AVLCreate(int (*comapre_func)(const void *,const void *))
{
    avl_tree_t *tree = NULL; 

    assert(NULL != comapre_func);

    tree = (avl_tree_t *)malloc(sizeof(avl_tree_t));
    if (NULL == tree)
    {
        return (NULL);
    }

    tree->root = NULL;
    tree->compare_func = comapre_func;

    return (tree);
}

/*Cuts down the tree*/
void AVLDestroy(avl_tree_t *tree)
{
    assert(NULL != tree);

    if (AVLIsEmpty(tree))
    {
        free(tree);
        return;
    }
    
    DestroyNode(GetRoot(tree));

    free(tree);
}

/*Inserts a new leaf*/
int AVLInsert(avl_tree_t *tree, void *data)
{
    avl_node_t *insert = NULL;

    assert(NULL != tree);

    insert = CreateLeaf(data);
    if (NULL == insert)
    {
        return (FAIL);
    }
    
    if (AVLIsEmpty(tree))
    {
        SetNewNode(tree, insert);

        return (SUCCESS);
    }

    if (NULL == BalancedInsert(tree, GetRoot(tree), insert))
    {
        return (FAIL);
    }

    return (SUCCESS);
}

/*Cuts a leafs*/
void AVLRemove(avl_tree_t *tree, void *data)
{
    assert(NULL != tree);
    assert(NULL != data);
    assert(!AVLIsEmpty(tree));

    RecRemove(tree,GetRoot(tree), data);
}


/*Gets the height of the tree*/
size_t AVLHeight(const avl_tree_t *tree)
{
    assert(NULL != tree);

    if (AVLIsEmpty(tree))
    {
        return (IS_EMPTY);
    }

    return (GetRoot((avl_tree_t *)tree)->node_level);
}

/*Is the tree naked*/
int AVLIsEmpty(const avl_tree_t *tree)
{
    assert(NULL != tree);

    return (NULL == GetRoot((avl_tree_t *)tree));
}

/*Operate on every leaf*/
int AVLForEach(avl_tree_t *tree, int traverse_type, 
               int (*call_back)(void *, void *), void *param)
{
	assert(NULL != tree);
    assert(NULL != call_back);

	switch (traverse_type)
    {
        case (PRE_ORDER):
            return(TraversePre(GetRoot(tree), call_back, param));
        case (IN_ORDER):
            return(TraverseIn(GetRoot(tree), call_back, param));
        case (POST_ORDER):
            return(TraversePost(GetRoot(tree), call_back, param)); 
        default:
            return (FAIL);
    }    
}

/*Counts the leaves*/
size_t AVLCount(const avl_tree_t *tree)
{
    size_t size = 0; 

    assert(NULL != tree);

    AVLForEach((avl_tree_t *)tree, IN_ORDER, GetSize, &size);

    return (size);
}

/*Finds a leaf*/
void *AVLFind(avl_tree_t *tree, const void *data)
{
    assert(NULL != tree);

    return (FindValue(tree, GetRoot(tree), (void *)data));
}

/*====================Static Funcs============================================*/
static avl_node_t *CreateLeaf(void *data)
{  
    avl_node_t *new_leaf = (avl_node_t *)malloc(sizeof(avl_node_t));
    if (NULL == new_leaf)
    {
        return (NULL);
    }

    SetHeight(new_leaf, LEAF_HEIGHT);
    SetChild(new_leaf, NULL, RIGHT);
    SetChild(new_leaf, NULL, LEFT);
    SetData(new_leaf, data);

    return (new_leaf);
}

static avl_node_t *GetChild(avl_node_t *node, int child)
{
    return (node->children[child]);
}

avl_node_t *GetRoot(avl_tree_t *tree)
{
    return (tree->root);
}

void *GetData(avl_node_t *node)
{
    return (node->data);
}

static size_t GetHeight(avl_node_t *node)
{
    if (NULL == node)
    {
        return (0);
    }
    return (node->node_level);
}

static void SetChild(avl_node_t *node, avl_node_t *new_child ,int child)
{
    node->children[child] = new_child;
}

static void SetData(avl_node_t *node, void *new_data)
{
    node->data = new_data;
}

static void SetHeight(avl_node_t *node, size_t new_level)
{
    node->node_level = new_level;
}

static int IsLeaf(avl_node_t *where)
{
    return (NULL == GetChild(where, RIGHT) && NULL == GetChild(where, LEFT));
}

static void SetNewNode(avl_tree_t *tree, avl_node_t *node)
{
    tree->root = node; 
}

static int GetSize(void *a, void *b)
{
	++(*(size_t *)b);
	
	(void)(a);
	
	return (SUCCESS);		
}

/*==================Comparison Funcs==============================*/
static int GetCompared(avl_tree_t *tree, void *to_check ,void *check_against)
{
    int status = 0; 

    assert(NULL != tree);

    if (NULL == to_check || NULL == check_against)
    {
        return (0);
    }
    
    status = tree->compare_func(to_check, check_against);

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

/*==================Balancing funcs==============================*/
static int IsHeigher(avl_node_t *check, avl_node_t *check_against)
{

    if (NULL == check)
    {
        return (GetHeight(check_against));
    }

    else if (NULL == check_against)
    {
        return (GetHeight(check));
    }
    
    return (GetHeight(check) > GetHeight(check_against) ? 
            GetHeight(check) : GetHeight(check_against));   
}

static int ToBalance(avl_node_t *current)
{
    if (IsLeaf(current))
    {
        return (0);
    }

    if (NULL == GetChild(current, LEFT))
    {
        return (GetHeight(GetChild(current, RIGHT)));
    }

    else if (NULL == GetChild(current, RIGHT))
    {
        return (GetHeight(GetChild(current, LEFT)));
    }
    
    return (GetHeight(GetChild(current, LEFT)) - 
            GetHeight(GetChild(current, RIGHT)));   
}

static avl_node_t *RotateLeft(avl_tree_t *tree, avl_node_t *current)
{
    avl_node_t *child = NULL;
    avl_node_t *grandchild = NULL;

    assert(NULL != current);
    
    child = GetChild(current, RIGHT);
    grandchild = GetChild(child, LEFT);

    SetChild(child, current, LEFT);
    SetChild(current, grandchild, RIGHT);

    SetHeight(current, IsHeigher(GetChild(current, LEFT), 
                                 GetChild(current, RIGHT)) + 1);
    SetHeight(child, IsHeigher(GetChild(child, LEFT), 
                               GetChild(child, RIGHT)) + 1);

    if (current == GetRoot(tree))
    {
        tree->root = child;
    }

    return (child);
}

static avl_node_t *RotateRight(avl_tree_t *tree, avl_node_t *current)
{
    avl_node_t *child = NULL;
    avl_node_t *grandchild = NULL;

    assert(NULL != current);
    
    child = GetChild(current, LEFT);
    grandchild = GetChild(child, RIGHT);

    SetChild(child, current, RIGHT);
    SetChild(current, grandchild, LEFT);

    SetHeight(current, IsHeigher(GetChild(current, LEFT), 
                                 GetChild(current, RIGHT)) + 1);
    SetHeight(child, IsHeigher(GetChild(child, LEFT), 
                               GetChild(child, RIGHT)) + 1);

    if (current == GetRoot(tree))
    {
        tree->root = child;
    }

    return (child);
}

static avl_node_t *BalancedInsert(avl_tree_t *tree, avl_node_t *where, 
                                  avl_node_t *insert)
{
    int new_dir = 0;
    int to_balance = 0; 
    int compare_left = 0; 
    int compare_right = 0;
    
    assert(NULL != where);
    assert(NULL != insert);

    new_dir = GetCompared(tree ,GetData(where), GetData(insert));
    if (FOUND == new_dir)
    {
        free(insert);
        return (NULL);
    }

    if (NULL == GetChild(where, new_dir))
    {
        SetChild(where, insert, new_dir);
        SetHeight(where, IsHeigher(GetChild(where, LEFT), 
                                   GetChild(where, RIGHT)) + 1);
        return (where);      
    }

    SetChild(where, 
             BalancedInsert(tree, GetChild(where, new_dir), insert), 
             new_dir);

    SetHeight(where, IsHeigher(GetChild(where, LEFT), 
                               GetChild(where, RIGHT)) + 1);

    to_balance = ToBalance(where);
    if (0 == to_balance)
    {
        return (where);
    }

    if (NULL != GetChild(where, LEFT))
    {    
        compare_left = GetCompared(tree ,GetData(insert), 
                               GetData(GetChild(where, LEFT)));

        if (to_balance > UPPER_BALANCE && 1 == compare_left)     
        {
            return (RotateRight(tree ,where));
        }

        if (to_balance > UPPER_BALANCE &&  0 == compare_left)
        {
            SetChild(where, RotateLeft(tree ,GetChild(where, LEFT)), LEFT);
            return (RotateRight(tree, where));
        }
    }
    
    if(NULL != GetChild(where, RIGHT))
    {
        compare_right = GetCompared(tree ,GetData(insert), 
                                GetData(GetChild(where, RIGHT)));
        
        if (to_balance < LOWER_BALANCE && 0 == compare_right)
        {
            return (RotateLeft(tree, where));
        }
        
        
        if (to_balance < LOWER_BALANCE && 1 == compare_right)
        {
            SetChild(where, RotateLeft(tree ,GetChild(where,RIGHT)), RIGHT);
            return (RotateLeft(tree, where));
        }  
    }

    return (where);
}

/*====================Recursive funcs========================================*/
static void DestroyNode(avl_node_t *to_free)
{
    if (NULL != GetChild(to_free, LEFT))
    {
        DestroyNode(GetChild(to_free, LEFT));
        SetChild(to_free, NULL, LEFT);
    }

    if (NULL != GetChild(to_free, RIGHT))
    {
        DestroyNode(GetChild(to_free, RIGHT));
        SetChild(to_free, NULL, RIGHT);
    }

    free(to_free);
}

avl_node_t *RecRemove(avl_tree_t *tree, avl_node_t *to_remove, void *data)
{
    avl_node_t *temp = NULL; 
    int dir_to_remove = 0;

    assert(NULL != tree);

    if (NULL == to_remove)
    {
        return (NULL);
    }

    if (IsLeaf(to_remove))
    {
        free(to_remove);
        return (NULL);
    }

    dir_to_remove = GetCompared(tree ,GetData(to_remove), data);

    if (LEFT == dir_to_remove)
    {
        SetChild(to_remove, 
                 RecRemove(tree, GetChild(to_remove, LEFT), data), 
                 LEFT);
    }

    else if (RIGHT == dir_to_remove)
    {
        SetChild(to_remove, 
                 RecRemove(tree, GetChild(to_remove, RIGHT), data),
                 RIGHT);
    }

    else
    {
        if (NULL == GetChild(to_remove, RIGHT))
        {
            temp = GetChild(to_remove, LEFT); 
            free(to_remove);
            return (temp);
        }
        
        else if (NULL == GetChild(to_remove, LEFT))
        {
            temp = GetChild(to_remove, RIGHT); 
            free(to_remove);
            return (temp);
        }   

        temp = GetChild(to_remove, LEFT);
        temp = TravesreDir(temp, RIGHT);
        SetData(to_remove, GetData(temp));

        SetChild(to_remove, 
                 RecRemove(tree, GetChild(to_remove,RIGHT), GetData(temp)),
                 RIGHT);   
    }

    return (to_remove);
}

/*===========================Traversals=======================================*/
static int TraversePre(avl_node_t *where, 
                         int (*call_back)(void *, void *), void *param)
{  
    assert(NULL != where);
    assert(NULL != call_back);

    if (NULL == where)
    {
       return (SUCCESS);
    }
    
    if (FAIL == call_back(GetData(where), param))
    {
        return (FAIL);
    }

    TraversePre(GetChild(where, LEFT), call_back, param);
    TraversePre(GetChild(where, RIGHT), call_back, param);
}

static int TraversePost(avl_node_t *where, 
                         int (*call_back)(void *, void *), void *param)
{
    assert(NULL != call_back);

    if (NULL == where)
    {
       return (SUCCESS);
    }
    
    TraversePost(GetChild(where, LEFT), call_back, param);
    TraversePost(GetChild(where, RIGHT), call_back, param);

    if (FAIL == call_back(GetData(where), param))
    {
        return (FAIL);
    }
}
static int TraverseIn(avl_node_t *where, 
                      int (*call_back)(void *, void *), void *param)
{  
    assert(NULL != call_back);

    if (NULL == where)
    {
       return (SUCCESS);
    }
    
    TraverseIn(GetChild(where, LEFT), call_back, param);

    if (FAIL == call_back(GetData(where), param))
    {
        return (FAIL);
    }

    TraverseIn(GetChild(where, RIGHT), call_back, param);
}

static void *FindValue(avl_tree_t *tree, avl_node_t *where, const void *param)
{  
    if (NULL == where)
    {
       return (NULL);
    }
    
    if (FOUND == GetCompared(tree ,GetData(where), (void *)param))
    {
        return (where);
    }

    FindValue(tree,GetChild(where, LEFT), param);
    FindValue(tree, GetChild(where, RIGHT), param);
}

static avl_node_t *TravesreDir(avl_node_t *where, int direction)
{
    while (NULL != GetChild(where, direction))
    {
        where = GetChild(where, direction);       
    }

    return (where);
}
