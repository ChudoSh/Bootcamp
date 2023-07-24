#include <stdio.h>

#define COUNT 10

typedef struct node
{
    void *data;
    struct node *parent;
    struct node *left;
    struct node *right;
} node_t;

static node_t *FindTail(node_t *node);
static void print2DUtil(node_t *root, int space);
static void print2D(node_t *root);

node_t *BSTToSortedList(node_t *root)
{
    node_t *left_list = NULL;
    node_t *right_list = NULL;
    node_t *left_list_tail = NULL;

    if (NULL == root)
    {
        return (NULL);
    }

    left_list = BSTToSortedList(root->left);
    right_list = BSTToSortedList(root->right);

    if (NULL == left_list && NULL == right_list)
    {
        return (root);
    }

    left_list_tail = FindTail(left_list);

    if (NULL != left_list_tail)
    {
        left_list_tail->right = root;
        root->left = left_list_tail;
    }

    root->right = right_list;

    if (NULL != right_list)
    {
        right_list->left = root;
    }

    return ((left_list != NULL) ? left_list : root);
}

static node_t *FindTail(node_t *node)
{
    if (node == NULL)
    {
        return (NULL);
    }

    while (node->right != NULL)
    {
        node = node->right;
    }

    return (node);
}

int main()
{
    int arr[8] = {4, 6, 8, 10, 12, 14, 16, 13};
    node_t *list = NULL;

    node_t node_4;
    node_t node_6;
    node_t node_8;
    node_t node_10;
    node_t node_12;
    node_t node_13;
    node_t node_14;
    node_t node_16;

    node_4.data = &arr[0];
    node_4.parent = &node_6;
    node_4.left = NULL;
    node_4.right = NULL;

    node_8.data = &arr[2];
    node_8.parent = &node_6;
    node_8.left = NULL;
    node_8.right = NULL;

    node_12.data = &arr[4];
    node_12.parent = &node_14;
    node_12.left = NULL;
    node_12.right = &node_13;

    node_13.data = &arr[7];
    node_13.parent = &node_12;
    node_13.left = NULL;
    node_13.right = NULL;

    node_16.data = &arr[6];
    node_16.parent = &node_14;
    node_16.left = NULL;
    node_16.right = NULL;

    node_6.data = &arr[1];
    node_6.parent = &node_10;
    node_6.left = &node_4;
    node_6.right = &node_8;

    node_14.data = &arr[5];
    node_14.parent = &node_10;
    node_14.left = &node_12;
    node_14.right = &node_16;

    node_10.data = &arr[3];
    node_10.parent = NULL;
    node_10.left = &node_6;
    node_10.right = &node_14;

    print2D(&node_10);

    list = BSTToSortedList(&node_10);

    printf("\n\n");

    while (NULL != list)
    {
        printf("%d ->", *(int *)list->data);
        list = list->right;
    }

    printf("\n");

    return (0);
}

static void print2DUtil(node_t *root, int space)
{
    int i = 0;

    if (root == NULL)
    {
        return;
    }

    space += COUNT;

    print2DUtil(root->right, space);

    printf("\n");

    for (i = COUNT; i < space; i++)
    {
        printf(" ");
    }

    printf("%d\n", *(int *)root->data);

    print2DUtil(root->left, space);

    printf("\n");
}

static void print2D(node_t *root)
{
    print2DUtil(root, 0);
}
