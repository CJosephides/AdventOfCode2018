#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


int find_unique_claim(int *matrix, char **input_data)
{
    /* Scan input data again. */
    int claim_id, left, top, width, height, i, j, l, overlaps;
    for (l = 0; l < INPUTSIZE; l++) {
        sscanf(input_data[l], "#%d @ %d,%d: %dx%d\n", &claim_id, &left, &top, &width, &height);
        /* Scan matrix. */
        overlaps = 0;
        for (i=top; i<top+height; i++) {
             for (j=left; j<left+width; j++) {
                 overlaps += matrix[j + i * MATSIZE]++;
             }
        }
        if (overlaps == width * height) 
            return claim_id;
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

    /* Allocate space for input data. */
    char **input_data = calloc(INPUTSIZE, sizeof(char *));

    /* Read file into memory line by line. */
    FILE *fp;
    fp = fopen("input.dat", "r");

    char buffer[LINELEN];
    int l = 0;
    while (fgets(buffer, LINELEN, fp) != NULL) {
        input_data[l] = malloc(LINELEN * sizeof(char)); 
        input_data[l] = strcpy(input_data[l], buffer);
        l++;
    }

    int claim_id, left, top, width, height, i, j;
    for (l = 0; l < INPUTSIZE; l++) {
        sscanf(input_data[l], "#%d @ %d,%d: %dx%d\n", &claim_id, &left, &top, &width, &height);
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
    printf("Unique claim id = %d.\n", find_unique_claim(matrix, input_data));

    free(matrix);
    free(input_data);
    return 0;
}
