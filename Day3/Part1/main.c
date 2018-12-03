#include <stdio.h>
#include <stdlib.h>
#define MATSIZE 1000
#define INPUTSIZE 1375
#define LINELEN 25

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

int find_unique_claim(int *matrix)
{
    /* Read file line by line. */
    char *lines[INPUTSIZE];
    FILE *fp;
    fp = fopen("input.dat", "r");

    char buffer[LINELEN];
    int claim_id, left, top, width, height, i, j, l, overlaps;
    for (l = 0; l < INPUTSIZE; l++) {
        fscanf(fp, "#%d @ %d,%d: %dx%d\n", &claim_id, &left, &top, &width, &height);
        /* Scan matrix. */
        overlaps = 0;
        for (i=top; i<top+height; i++) {
             for (j=left; j<left+width; j++) {
                 overlaps += matrix[j + i * MATSIZE];
             }
        }
        if (overlaps == width * height) {
            fclose(fp);
            return claim_id;
        }
    }
    return -1;
}

int main(int argc, char **argv)
{

    /* Allocate space for a 2D matrix. */
    int *matrix = (int *) calloc(MATSIZE * MATSIZE, sizeof(int));
    if (matrix == NULL) {
        printf("Error. Could not allocate heap.\n");
        exit(1);
    } 

    /* Read file line by line. */
    char *lines[INPUTSIZE];
    FILE *fp;
    fp = fopen("input.dat", "r");

    char buffer[LINELEN];
    int claim_id, left, top, width, height, i, j, l;
    for (l = 0; l < INPUTSIZE; l++) {
        fscanf(fp, "#%d @ %d,%d: %dx%d\n", &claim_id, &left, &top, &width, &height);
        /* Update matrix. */
        for (i=top; i<top+height; i++) {
             for (j=left; j<left+width; j++) {
                 matrix[j + i * MATSIZE]++;
             }
        }
    }

    fclose(fp);

    //print_matrix(matrix);
    printf("Found %d overlaps.\n", count_overlaps(matrix));
    printf("Unique claim id = %d.\n", find_unique_claim(matrix));

    free(matrix);  // deallocate our matrix
    return 0;
}
