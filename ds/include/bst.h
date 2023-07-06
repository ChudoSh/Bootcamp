/*
Dev: BarSH
Rev: 
Date: .6.23
Status: 
*/

#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct BSTNode bst_node_t;
/*
struct BSTNode
{
    bst_node_t *parent;
    bst_node_t *children[NUM_OF_CHILDREN];
    void *value;
};
*/

typedef bst_node_t *bst_iter_t;

typedef struct BST bst_t;
/*
struct BST
{
    bst_node_t root_stub;
    int (*compare_func)(const void *a, const void *b);
};
*/

enum CHILDREN
{
	LEFT,
	RIGHT,
    NUM_OF_CHILDREN
};

/******************************************************************************/
/*
Description: Create a binary search tree.
Arguments: 
    compare_func - function used to determine which of two element is larger
Return: Pointer to the created binary search tree.

Time complexity: O(1)
Space complexity: O(1)
*/

bst_t *BSTCreate(int (*compare_func)(const void *a, const void *b));

/******************************************************************************/
/*
Description: Destroy a binary search tree.
Arguments: 
    tree - a valid binary search tree pointer to the tree to be destroyed
Return: 
    Void.
Time complexity: O(n)
Space complexity: O(1)
*/

void BSTDestroy(bst_t *tree);

/******************************************************************************/
/*
Description: Insert a new value into a binary search tree.
Arguments:
    tree - a valid tree pointer to the tree to be inserted into
    data - a valid pointer to the data to be inserted. Trying to insert data
                that is already present in the tree will result in failure.
Return: 
    If successful - iterator at the inserted value. 
    If failed - returns BSTEnd(tree).
Time complexity: O(log(n)), WC - O(n)
Space complexity: O(1)
*/

bst_iter_t BSTInsert(bst_t *tree, void *data);

/******************************************************************************/
/*
Description: Remove a node from the tree.
Arguments: 
    current - an iterator at the node to be removed
Return: Void.

Time complexity: O(log(n)), WC - O(n)
Space complexity: O(1)
*/

void BSTRemove(bst_iter_t current);

/******************************************************************************/
/*
Description: Move to the next node in the tree.
Arguments: 
    current - an iterator at the node to move from
Return: An iterator at the next node.

Time complexity: O(log(n))
Space complexity: O(1)
*/

bst_iter_t BSTNext(bst_iter_t current);

/******************************************************************************/
/*
Description: Move to the previous node in the tree.
Arguments: 
    current - an iterator at the node to move from
Return: An iterator at the previous node.

Time complexity: O(log(n))
Space complexity: O(1)
*/

bst_iter_t BSTPrev(bst_iter_t current);

/******************************************************************************/
/*
Description: Get the number of nodes in the tree.
Arguments: 
    tree - a valid tree pointer to the tree to be examined
Return: Number of nodes in given tree.

Time complexity: O(n)
Space complexity: O(1)
*/

size_t BSTSize(const bst_t *tree);

/******************************************************************************/
/*
Description: Get data from a node in the tree.
Arguments: 
    where - an interator at the node whose data should be returned
Return: Pointer to the data.

Time complexity: O(1)
Space complexity: O(1)
*/

void *BSTGetData(bst_iter_t where);

/******************************************************************************/
/*
Description: Get the left-most node in the tree.
Arguments: 
    tree - a valid tree pointer to the tree to be examined
Return: An iterator at the left-most tree node.

Time complexity: O(log(n))
Space complexity: O(1)
*/

bst_iter_t BSTBegin(const bst_t *tree);

/******************************************************************************/
/*
Description: Get the right-most node in the tree.
Arguments: 
    tree - a valid tree pointer to the tree to be examined
Return: An iterator at the right-most tree node.

Time complexity: O(1)
Space complexity: O(1)
*/

bst_iter_t BSTEnd(const bst_t *tree);

/******************************************************************************/
/*
Description: Check if a tree is empty.
Arguments: 
    tree - a valid tree pointer to the tree to be examined
Return: TRUE (1) if empty, FALSE (0) if not.

Time complexity: O(1)
Space complexity: O(1)
*/

int BSTIsEmpty(const bst_t *tree);


/******************************************************************************/
/*
Description: Find a certain value in the tree.
Arguments: 
    tree  - a valid tree pointer to the tree to be examined
    param - the value to be searched for
Return: An iterator at the node containing the value. If not found, returns end.

Time complexity: O(log(n)), WC - O(n)
Space complexity: O(1)
*/

bst_iter_t BSTFind(bst_t *tree, const void *param);

/******************************************************************************/
/*
Description: Perform an action on all the nodes of a tree.
Arguments: 
    from      - an iterator at the place to begin performing action
    to        - an iterator at the place to finish performing action (excluded)
    call_back - a function performing the desired action
    param     - a valid pointer to a call_back parameter
Return: SUCCESS (0) upon successful performance of all actions, FAIL (-1) upon 
        failure.

Time complexity: O(n)
Space complexity: O(1)
*/

int BSTForEach(bst_iter_t from, bst_iter_t to, int (*call_back)(void *, void *), void *param);

/******************************************************************************/
/*
Description: Check if two iterators are at the same node.
Arguments: 
    iter1 - the first iterator to be compared
    iter2 - the second iterator to be compared
Return: TRUE (1) if same, FALSE (0) if not.

Time complexity: O(1)
Space complexity: O(1)
*/

int BSTIsSameIter(const bst_iter_t iter1, bst_iter_t iter2);

#endif /* __BST_H__ */
