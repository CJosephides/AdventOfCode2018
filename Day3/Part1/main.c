#include <stdio.h>
#include <stdlib.h>
#define MATSIZE 1000

int *matrix;

/* Print the matrix. */
void print_matrix(int *matrix)
{

    int i, j;
    for (i=0; i<MATSIZE; i++) {
        for (j=0; j<MATSIZE; j++) {
            putchar('0' + matrix[j + i * MATSIZE]);
        }
        putchar('\n');
    }

    return;
}

/* Count overlaps in matrix. */
int count_overlaps(int *matrix)
{
    int i, j, overlaps = 0;
    for (i=0; i<MATSIZE; i++) {
        for (j=0; j<MATSIZE; j++) {
            if (matrix[j + i * MATSIZE] > 1) {
                overlaps++;
            }
        }
    }

    return overlaps;
}

int main(int argc, char **argv)
{

    /* Allocate space for a 2D matrix. */
    int *matrix = (int *) calloc(MATSIZE * MATSIZE, sizeof(int));
    if (matrix == NULL) {
        printf("Error. Could not allocate heap.\n");
        exit(1);
    } 

    /* Read stdin line by line. */
    int claim_id, left, top, width, height, i, j;
    while (scanf("#%d @ %d,%d: %dx%d\n", &claim_id, &left, &top, &width, &height) == 5) {
        //printf("claim=%d, left=%d, top=%d, width=%d, height=%d\n", claim_id, left, top, width, height);
        /* Update matrix. */
       for (i=top; i<top+height; i++) {
            for (j=left; j<left+width; j++) {
                matrix[j + i * MATSIZE]++;
            }
       }
    }

    //print_matrix(matrix);
    printf("Found %d overlaps.\n", count_overlaps(matrix));

    free(matrix);  // deallocate our matrix
    return 0;
}
