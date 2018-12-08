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

    print_graph_dependencies(graph);

    /* Initialize workers. */
    int w;
    Worker *workers = calloc(5, sizeof(Worker));
    for (w = 0; w < 5; w++) {
        workers[w].busy = 0;
        workers[w].node = NULL;
        workers[w].finish_time = -1;
    }

    int time = 0;
    while (graph->next != NULL || num_busy_workers(workers) > 0) {

        /* Check if any workers have finished. */
        for (w = 0; w < 5; w++) {
            if (workers[w].finish_time == time) {
                remove_dependency_from_all_nodes(workers[w].node->c, graph);
                workers[w].busy = 0;
                workers[w].node = NULL;
                workers[w].finish_time = -1;
            }
        }

        /* Assign new tasks to workers, as much as we can. */
        NodePtr next_node;
        while ((next_node = next_node_without_dependencies(graph)) != NULL) {
            if (num_busy_workers(workers) == 5) {
                break;
            } else {
                // remove from graph
                remove_node(next_node->c, graph);
                // assign to worker
                w = next_free_worker_index(workers);
                workers[w].busy = 1;
                workers[w].node = next_node;
                workers[w].finish_time = time + 60 + ((next_node->c) - 64);
            }
        }

        /* Increment time. */
        time++;
    }


    printf("Total time = %d.\n", time - 1);
    return 0;
}
