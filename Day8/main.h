#ifndef _H_NODE
#define _H_NODE

typedef struct node {
    int index;
    int n_children;
    int n_metadata;
    int metadata_sum;
} Node, *NodePtr;

#endif
