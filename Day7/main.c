#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#define INPUT_FILE "input.dat"


int main(int argc, char **argv)
{

    /* Initialize graph. */
    NodePtr graph = malloc(sizeof(Node));
    graph->c = '\0';
    graph->next = NULL;

    /*
    NodePtr a = insert_node('A', graph);
    NodePtr b = insert_node('B', graph);
    NodePtr c = insert_node('C', graph);
    NodePtr d = insert_node('D', graph);
    NodePtr e = insert_node('E', graph);
    NodePtr f = insert_node('F', graph);

    insert_dependency('C', find_node('A', graph));
    insert_dependency('C', find_node('F', graph));
    insert_dependency('A', find_node('B', graph));
    insert_dependency('A', find_node('D', graph));
    insert_dependency('B', find_node('E', graph));
    insert_dependency('D', find_node('E', graph));
    insert_dependency('F', find_node('E', graph));

    print_graph_dependencies(graph);
    */

    /* Read in graph from file. */
    FILE *fp = fopen(INPUT_FILE, "rb");
    char source, destination;
    while (fscanf(fp,
                  "Step %c must be finished before step %c can begin.\n",
                  &source, &destination) == 2) {

        if (find_node(source, graph) == NULL)
            insert_node(source, graph);
        if (find_node(destination, graph) == NULL)
            insert_node(destination, graph);

        insert_dependency(source, find_node(destination, graph));
    }
    fclose(fp);

    print_graph_dependencies(graph);

    NodePtr node_to_pop;
    NodePtr node;
    while ((node_to_pop = next_node_without_dependencies(graph)) != NULL) {
        for (node = graph; node != NULL; node = node->next) {
            remove_dependency(node_to_pop->c, node);
        }
        remove_node(node_to_pop->c, graph);
        printf("%c", node_to_pop->c);
    }
    printf("\n");

    return 0;
}
