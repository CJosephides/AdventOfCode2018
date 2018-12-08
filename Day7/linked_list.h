#ifndef _LINKED_LIST
#define _LINKED_LIST

typedef struct dependency {
    char c;
    struct dependency *next;
} Dependency, *DependencyPtr;

typedef struct node {
    char c;
    struct node *next;
    DependencyPtr dependencies;
} Node, *NodePtr;

NodePtr insert_node(char c, NodePtr graph);
NodePtr find_node(char c, NodePtr graph);
int print_graph(NodePtr graph);
NodePtr remove_node(char c, NodePtr graph);

DependencyPtr insert_dependency(char c, NodePtr node);
int print_dependencies(NodePtr node);
DependencyPtr remove_dependency(char c, NodePtr node);

int print_graph_dependencies(NodePtr graph);

NodePtr next_node_without_dependencies(NodePtr graph);

#endif
