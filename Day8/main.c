#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
//#define INPUT_FILE "small_input.dat"
//#define INPUT_CHAR_MAX 36
//#define INPUT_MAX 16
#define INPUT_FILE "input.dat"
#define INPUT_CHAR_MAX 34983
#define INPUT_MAX 17359

int global_sum = 0;


NodePtr visit(int *index, int *array)
{
    /* Make a new node */
    NodePtr node = malloc(sizeof(Node));
    node->index = *index;
    node->value = 0;

    node->n_children = array[(*index)++];  // tricky
    node->children = calloc(node->n_children, sizeof(Node));

    node->n_metadata = array[(*index)++];  // also tricky
    node->metadata = calloc(node->n_metadata, sizeof(int));

    node->metadata_sum = 0;

    /*
    printf("Making new node at index = %d. It has %d children and %d metadata.\n", node->index, node->n_children, node->n_metadata);
    */

    /* Visit its children. */
    int c = 0;
    NodePtr child;
    for (c = 0; c < node->n_children; c++) {
        child = visit(index, array);  // index is a pointer, and will be incremented recursively
        node->children[c] = *child;
    }

    /* Gather its metadata. */
    int m = 0;
    int data;
    for (m = 0; m < node->n_metadata; m++) {
        data = array[(*index)];
        node->metadata[m] = data;
        node->metadata_sum += array[(*index)++];  // tricky
    }

    int child_number;
    /* Get value. */
    if (node->n_children == 0) {
        // Just its metadata sum.
        node->value = node->metadata_sum;
    } else {
       // Sum of the (valid) childrens' values. 
       for (m = 0; m < node->n_metadata; m++) {
           child_number = node->metadata[m];
           if (child_number != 0 && child_number <= node->n_children) {
               // If the child with that number exists.
               node->value += node->children[child_number-1].value;
           }
       }
    }

    global_sum += node->metadata_sum;

    /*
    printf("The metadata sum for node at index %d = %d.\n", node->index, node->metadata_sum);
    */

    if (node->index == 0) {
        printf("The value of the root is %ld.\n", node->value);
    }

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
