#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum KIDS
{
    LEFT,
    RIGHT,
    NUM_OF_KIDS
};

typedef struct NODE node_tree_t;
struct NODE
{
    void *value;
    node_tree_t *kids[2];  
};


int IsLeaf(node_tree_t *root);
void GenericSwap(void *a, void *b);
void TreeToList(node_tree_t *root);

int main()
{
    int arr[7] = {10, 6, 14, 4, 8, 12, 16};
    node_tree_t *root = (node_tree_t *)malloc(sizeof(node_tree_t));
    if (NULL == root)
    {
        perror("malloc");
        return (-1);
    }

    root->value = &arr[0];
    root->kids[LEFT]->value = &arr[1];
    root->kids[RIGHT]->value = &arr[2];
    root->kids[LEFT]->kids[LEFT]->value = &arr[3];
    root->kids[LEFT]->kids[RIGHT]->value = &arr[4];
    root->kids[RIGHT]->kids[LEFT]->value = &arr[5];
    root->kids[RIGHT]->kids[RIGHT]->value = &arr[6];

    TreeToList(root);

    return (0);   
}

node_tree_t *TreeToList(node_tree_t *root)
{
    node_tree_t *iter = NULL;
    node_tree_t *temp = NULL; 

    if (IsLeaf(root) || NULL == root)
    {
        return;
    } 

    if (NULL != root->kids[LEFT])
    {
        TreeToList(root->kids[LEFT]);

        temp = root->kids[RIGHT];
        root->kids[RIGHT] = root->kids[LEFT];
        root->kids[LEFT] = NULL;

        iter = root->kids[RIGHT];
        while (NULL != iter->kids[RIGHT])
        {
            iter = iter->kids[RIGHT];
        }

        iter->kids[RIGHT] = temp; 
    }

    TreeToList(root->kids[RIGHT]);
   
    /*GenericSwap(root->value, root->kids[RIGHT]->value);

    root->kids[RIGHT]->kids[LEFT] = root->kids[LEFT]; 
    root->kids[LEFT]->kids[RIGHT] = root->kids[RIGHT];
    root->kids[LEFT] = NULL;
    
    TreeToList(root->kids[RIGHT]);
    GenericSwap(root->value, root->kids[LEFT]->value);

    root->kids[RIGHT]->kids[LEFT] = root->kids[LEFT]; 
    root->kids[LEFT]->kids[RIGHT] = root->kids[RIGHT];
    root->kids[RIGHT] = NULL;*/
}

void GenericSwap(void *a, void *b)
{
    char temp = *(char *)a;
    memcpy(a, b, sizeof(void *));
    memcpy(b, &temp, sizeof(void *));
}

int IsLeaf(node_tree_t *root)
{
    return (NULL == root->kids[LEFT] && NULL == root->kids[RIGHT]);
}
