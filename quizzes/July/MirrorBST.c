#include <stdio.h>
#include "../ds/include/bst.h"

typedef struct node
{
    void *value;
    node_tree_t *kids[2];
    
}node_tree_t;


void MirrorBst(node_tree_t *root);

int main()
{
    int arr[5] = {2, 5,3 ,1 ,4};
    int i = 0; 

    return (0);   
}

void MirrorBst(node_tree_t *root)
{
    node_tree_t *temp = NULL; 

    if (NULL == root)
    {
        return;
    }

    MirrorBst(root->kids[0]);
    MirrorBst(root->kids[1]);

    temp = root->kids[0];
    root->kids[0] = root->kids[1];
    root->kids[1] = temp;
}
