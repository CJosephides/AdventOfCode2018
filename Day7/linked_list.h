#ifndef _LINKED_LIST
#define _LINKED_LIST

typedef struct dependency {
    char c;
    struct dependency *next;
} Dependency, *DependencyPtr;

typedef struct node {
    char c;
    struct node *next;
    int in_progress;
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

typedef struct worker {
    int busy;
    NodePtr node;
    int finish_time;
} Worker, *WorkerPtr;

int num_busy_workers(WorkerPtr workers);
int next_free_worker_index(WorkerPtr workers);

void remove_dependency_from_all_nodes(char c, NodePtr graph);

#endif
