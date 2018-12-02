#include <stdio.h>
#define MAXLINE 30


int main(int argc, char **argv)
{

    /* Initialize repeat counts. */
    int counts[MAXLINE];
    int i;
    for (i = 0; i < MAXLINE; counts[i++] = 0);  // can't use 1s here!

    /* Read input line by line. */
    FILE *fp;
    fp = fopen("input.dat", "rb");

    char line[MAXLINE];
    while (fgets(line, MAXLINE, fp) != NULL) {

        /* Keep a tally for each letter of the alphabet. */
        int alphabet[26] = {0};
        for (i = 0; i < 26; alphabet[i++] = 0);

        /* Iterate through the string and update tally. */
        for (i = 0; (i < MAXLINE) && (line[i] != '\0'); i++) {
            alphabet[line[i] - 97]++;
        }

        /* Update repeat counts, but only once per repeat per word. */
        int seen[26];
        for (i = 0; i < 26; seen[i++] = 0);

        for (i = 0; i < 26; i++) {
            if ((alphabet[i] > 1) && (seen[alphabet[i]] == 0)) { 
                counts[alphabet[i]]++;
                seen[alphabet[i]] = 1;
            }
        }
                
    }

    /* Multiply repeat counts (that are not zero). */
    long product = 1;
    for (i = 0; i < MAXLINE; i++) {
        if (counts[i] > 0)
            product *= counts[i];
    }

    printf("checksum = %ld\n", product);

    return 0;
}
