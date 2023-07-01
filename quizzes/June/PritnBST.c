#include <stdio.h>
#include <assert.h>

#include "../ds/include/queue.h"

enum children 
{
    LEFT,
    RIGHT, 
    NUM_KIDS
};

typedef struct tree_node
{
    int *value; 
    bst_node_t *children[NUM_KIDS];
}bst_node_t;

void PrintTreeLevel(bst_node_t *tree);

int main(void)
{
    bst_node_t *tree = (bst_node_t*)malloc(sizeof(bst_node_t));
    PrintInTree(tree);
    return (0);
}

void PrintTreeLevel(bst_node_t *tree)
{
    bst_node_t *runner = NULL; 
    queue_t *queue = QCreate();
    if (NULL == queue)
    {
        return; 
    }

    assert(NULL != tree);

    runner = tree; 

    while (NULL != runner)
    {
        printf("%d\n", runner->value);
        
        if (NULL != runner->children[LEFT])
        {
            QEnqueue(queue, runner->children[LEFT]);
        }

        if (NULL != runner->children[RIGHT])
        {
            QEnqueue(queue, runner->children[RIGHT]);
        }

        runner = (bst_node_t *)QPeek(queue);
        QDequeue(queue);
    }
}
