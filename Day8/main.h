#ifndef _H_NODE
#define _H_NODE

typedef struct node {
    int index;
    long value;
    int n_children;
    struct node *children;
    int n_metadata;
    int *metadata;
    int metadata_sum;
} Node, *NodePtr;

#endif
