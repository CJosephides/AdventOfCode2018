#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NUMLINES 250
#define MAXLINE 30

/* Return common characters in the two strings, allowing for
 * one mismatch; otherwise, returns NULL. */
int str_almostmatch(char *first, char *second, char *matches)
{

    int n_matches = 0;
    int n_mismatches = 0;
    int i;

    /* Clear matches first. */
    matches[0] = '\0';

    for (i = 0; i < MAXLINE; i++) {
        if (first[i] == second[i]) {
            matches[n_matches++] = first[i];
        } else if ( n_mismatches++ > 1 )
            return 0;
    }

    matches[n_matches++] = '\0';
    return n_matches;
}

int main(int argc, char **argv)
{

    /* Read the input to memory. */
    char *lines[NUMLINES]; 

    FILE *fp;
    fp = fopen("input.dat", "r");
    
    int i;
    char buffer[MAXLINE];
    for (i = 0; i < NUMLINES; i++) {
        fgets(buffer, MAXLINE, fp);
        lines[i] = (char *) malloc(sizeof(char[MAXLINE]));
        strcpy(lines[i], buffer);
    }

    /* Quadratic half-pass to find almost-matches. */
    int j;
    char found_it = 0;
    char matches[MAXLINE];
    for (i = 0; (i < NUMLINES) && (found_it == 0); i++) {
        for (j = i+1; j < NUMLINES; j++ ) {
            if (str_almostmatch(lines[i], lines[j], matches) > 0) {
                found_it = 1;
                break;
            }
        }
    }

    printf("matches = %s", matches);
    return 0;
}
