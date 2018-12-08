#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#define INPUT_FILE "input.dat"
#define INPUT_CHAR_MAX 34983
#define INPUT_MAX 17359

int global_sum = 0;


NodePtr visit(int *index, int *array)
{
    /* Make a new node */
    NodePtr node = malloc(sizeof(Node));
    node->index = *index;
    node->n_children = array[(*index)++];  // tricky
    node->n_metadata = array[(*index)++];  // also tricky
    node->metadata_sum = 0;

    /*
    printf("Making new node at index = %d. It has %d children and %d metadata.\n", node->index, node->n_children, node->n_metadata);
    */

    /* Visit its children. */
    int c = 0;
    for (c = 0; c < node->n_children; c++) {
        visit(index, array);  // index is a pointer, and will be incremented recursively
    }

    /* Gather its metadata. */
    int m = 0;
    for (m = 0; m < node->n_metadata; m++) {
        node->metadata_sum += array[(*index)++];  // tricky
    }

    global_sum += node->metadata_sum;

    printf("The metadata sum for node at index %d = %d.\n", node->index, node->metadata_sum);

    return node;
}

int main(int argc, char **argv)
{
    /* Read the input. */
    char *str_input = malloc(INPUT_CHAR_MAX * sizeof(char));
    FILE *fp = fopen(INPUT_FILE, "rb");
    fgets(str_input, INPUT_CHAR_MAX, fp);
    fclose(fp);

    /*
    printf("Read: %s\n", str_input);
    */

    /* Put the words in an int array. */
    int *input = calloc(INPUT_MAX, sizeof(int));
    char *token = strtok(str_input, " ");

    int index = 0;
    while (token != NULL) {
        input[index] = atoi(token);
        index++;
        token = strtok(NULL, " ");
    }

    /*
    printf("Intd: ");
    for (index = 0; index < INPUT_MAX; index++) {
        printf("%d ", input[index]);
    }
    printf("\n");
    */

    index = 0;
    visit(&index, input);
    printf("Global metadata sum = %d.\n", global_sum);
    
    return 0;
}
