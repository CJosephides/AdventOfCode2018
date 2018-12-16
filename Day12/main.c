#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#define MAXPAT 6
#define LINEHLEN 2000
#define PATLEN 5

void print_position(const char *position)
{
    int i;
    for (i = 0; i < LINEHLEN; i++)
        putc(' ', stdout);
    putc('v', stdout);
    putc('\n', stdout);

    printf("%s\n", position);
}

void update(char *current_line, const Pattern *patterns, int n_patterns, char *next_line)
{
    /* Initialize the next line as a copy of the current one. */
    strcpy(next_line, current_line);

    /* Iterate through each pattern. */
    int i;
    for (i = 0; i < n_patterns; i++) {
        char *found = current_line;
        while ((found = strstr(found, patterns[i].string)) != NULL) {
            //printf("Found a match for rule %d at position %ld.\n", i, found - current_line);
            next_line[found - current_line + 2] = patterns[i].result;
            //found += PATLEN;
            found += 1;
        }
    }

}

/* Arguments:
 * 1: patterns file
 * 2: initial state file
 * 3: number of updates */
int main(int argc, char **argv)
{
    /* Read in patterns. */
    FILE *fp = fopen(argv[1], "rb");

    /* First pass: count number of lines/patterns. */
    char c;
    int n_patterns = 0;
    while ((c = fgetc(fp)) != EOF)
        if (c == '\n')
            n_patterns++;

    /* Populate patterns array. */
    rewind(fp);
    Pattern patterns[n_patterns];
    
    char string[MAXPAT];
    char result;
    int i;
    for (i = 0; i < n_patterns; i++) {
        fscanf(fp, "%s => %c", string, &result);
        patterns[i].string = calloc(MAXPAT, sizeof(char));
        patterns[i].result = result;
        strcpy(patterns[i].string, string);
    }

    fclose(fp);

    for (i = 0; i < n_patterns; i++) {
        //printf("[%d] Read pattern: %s => %c\n", i, patterns[i].string, patterns[i].result);
    }

    /* Initialize a string to hold the current line. */
    char current_line[1 + 2 * LINEHLEN];

    /* Read in initial position. */
    fp = fopen(argv[2], "rb");
    fscanf(fp, "initial state: %s\n", current_line + LINEHLEN);

    for (i = 0; i < 1 + 2 * LINEHLEN; i++) {
        if (current_line[i] != '#')
            current_line[i] = '.';
    }
    current_line[2 * LINEHLEN] = '\0';

    fclose(fp);
    //print_position(current_line);

    /* Update. */
    int q;
    char *next_line = calloc(1 + 2 * LINEHLEN, sizeof(char));
    for (i = 0; i < atoi(argv[3]); i++) {
        update(current_line, patterns, n_patterns, next_line);
        //print_position(next_line);
        strcpy(current_line, next_line);

        /* Sum plants. */
        int sum = 0;
        for (q = 0; q < 1 + 2 * LINEHLEN; q++) {
            if (current_line[q] == '#') {
                sum += q - LINEHLEN;
            }
        }
        printf("%d,%d\n", i, sum);
    }


    return 0;
}
