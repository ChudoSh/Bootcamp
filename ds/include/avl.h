/*
Developer:BarSH
Reviewer:MariaP
status: Approved
date: 18/06/23
*/
#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */


enum traverse_type
{
    IN_ORDER,
    POST_ORDER,
    PRE_ORDER
};

typedef struct AVL avl_tree_t;
typedef struct AVL_NODE avl_node_t;

/******************************************************************************/
/*
Description: Create an AVL.
Arguments: 
    compare_func - function used to determine which of two element is larger
Return: Pointer to the created AVL.

Time complexity: O(1)
Space complexity: O(1)
*/
avl_tree_t *AVLCreate(int (*comapre_func)(const void *,const void *));

/******************************************************************************/
/*
Description: Destroy a AVL.
Arguments: 
    tree - a valid binary search tree pointer to the tree to be destroyed
Return: Void.

Time complexity: O(n)
Space complexity: O(1)
*/
void AVLDestroy(avl_tree_t *tree);

/******************************************************************************/
/*
Description: Insert a new value into a AVL.
Arguments: 
    tree - a valid tree pointer to the tree to be inserted into
    data - a valid pointer to the data to eb inserted
Return: Iterator at the inserted value.

Time complexity: O(log(n))
Space complexity: O(1)
*/
int AVLInsert(avl_tree_t *tree, void *data);

/******************************************************************************/
/*
Description: Remove a node from the tree.
Arguments: 
    tree - a valid tree pointer to the data to be removed from
    data - the data value of the node to be removed

Time complexity: O(log(n))
Space complexity: O(1)
*/
void AVLRemove(avl_tree_t *tree, void *data);

/******************************************************************************/
/*
Description: Find a certain value in the tree.
Arguments: 
    tree  - a valid tree pointer to the tree to be examined
    data - the value to be searched for
Return: A pointer to data . If not found, returns NULL.

Time complexity: O(log(n))
Space complexity: O(1)
*/
void *AVLFind(avl_tree_t *tree, const void *data);

/******************************************************************************/
/*
Description: Perform an action on all the nodes of a tree.
Arguments: 
    tree  - a valid tree pointer to the tree where the call_back work on
    traverse_type  - enum represents the order of effect on the nodes
    call_back - a function performing the desired action
    param     - a valid pointer to a call_back parameter
Return: SUCCESS (0) upon successful performance of all actions, or the status of the failed action upon 
        failure note:failure stops the iteration.

Time complexity: O(n)
Space complexity: O(1)
*/
int AVLForEach(avl_tree_t *tree, int traverse_type, int (*call_back)(void *, void *), void *param);

/******************************************************************************/
/*
Description: Check if a tree is empty.
Arguments: 
    tree - a valid tree pointer to the tree to be examined
Return: TRUE (1) if empty, FALSE (0) if not.

Time complexity: O(1)
Space complexity: O(1)
*/
int AVLIsEmpty(const avl_tree_t *tree);

/******************************************************************************/
/*
Description: Get the number of nodes in the tree.
Arguments: 
    tree - a valid tree pointer to the tree to be examined
Return: maximum height in the given tree.

Time complexity: O(1)
Space complexity: O(1)
*/
size_t AVLHeight(const avl_tree_t *tree);

/******************************************************************************/
/*
Description: Get the number of nodes in the tree.
Arguments: 
    tree - a valid tree pointer to the tree to be examined
Return: Number of nodes in given tree.

Time complexity: O(n)
Space complexity: O(1)
*/
size_t AVLCount(const avl_tree_t *tree);

void PrintTree(avl_tree_t *tree);
avl_node_t *GetRoot(avl_tree_t *tree);
void *GetData(avl_node_t *node);


#endif /* __AVL_H__ */