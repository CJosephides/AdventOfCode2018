#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>


NodePtr insert_node(char c, NodePtr graph)
{

    /* Make the new node. */
    NodePtr new_node_ptr = malloc(sizeof(Node));
    new_node_ptr->c = c;
    new_node_ptr->next = NULL;
    new_node_ptr->dependencies = NULL;

    /* Insert while maintaining alphabetical sorting. */
    while (graph->next != NULL) {
        if (c < graph->next->c) {
            new_node_ptr->next = graph->next;
            graph->next = new_node_ptr;
            return new_node_ptr;
        }
        graph = graph->next;
    }
    
    /* Reached end of list; insert here. */
    graph->next = new_node_ptr;
    new_node_ptr->next = NULL;

    return new_node_ptr;
}

int print_graph(NodePtr graph)
{
    int n = 0;
    
    while (graph->next != NULL) {
        graph = graph->next;
        printf("%c", graph->c);
        n++;
    }

    printf("\n");
    return n;
}

NodePtr remove_node(char c, NodePtr graph)
{

    NodePtr removed_node;
    while (graph->next != NULL) {
        if (graph->next->c == c) {
            removed_node = graph->next;
            graph->next = graph->next->next;
            return removed_node;
        }
        graph = graph->next;
    }

    /* We couldn't find that char. */
    return NULL;
}

NodePtr find_node(char c, NodePtr graph)
{
    NodePtr node = graph;
    while (node != NULL) {
        if (node->c == c)
            return node;
        else
            node = node->next;
    }

    return NULL;
}

DependencyPtr insert_dependency(char c, NodePtr node)
{
    DependencyPtr dep = malloc(sizeof(Dependency));
    dep->c = c;
    dep->next = node->dependencies;
    node->dependencies = dep;
    return dep;
}

DependencyPtr remove_dependency(char c, NodePtr node)
{

    DependencyPtr dep = node->dependencies;
    if (dep == NULL)
        return NULL;

    if (dep->c == c) {
        node->dependencies = dep->next;
        return dep;
    }

    DependencyPtr prev_dep;
    while (dep->next != NULL) {
        prev_dep = dep;
        dep = dep->next;
        if (dep->c == c) {
            prev_dep->next = dep->next;
            return dep;
        }
    }

    return NULL;
}

int print_dependencies(NodePtr node)
{
    int n = 0;
    DependencyPtr dep = node->dependencies;

    while (dep != NULL) {
        printf("%c", dep->c);
        n++;
        dep = dep->next;
    }
    printf("\n");
    return n;
}

int print_graph_dependencies(NodePtr graph)
{
    int n;
    NodePtr node = graph->next;
    while (node != NULL) {
        n++;
        printf("%c: ", node->c);
        print_dependencies(node);
        node = node->next;
    }
    printf("\n");
    return n;
}

NodePtr next_node_without_dependencies(NodePtr graph)
{
    NodePtr node = graph->next;
    while (node != NULL) {
        if ((node->dependencies) == NULL) {
            return node;
        }
        node = node->next;
    }

    return NULL;
}
