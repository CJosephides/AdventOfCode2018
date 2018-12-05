#include <stdio.h>
#include "stack.h"

int main(int argc, char **argv)
{

    FILE *fp = fopen(argv[1], "rb");

    char c;
    while ((c = getc(fp)) != EOF) {
        polymerize(c);
    }

    int polymer_size;
    polymer_size = dump();
    printf("Initial polymer size = %d.\n", polymer_size);

    /* Part 2 */
    purge();

    int i, letters[26], min_letter, min_length = 100000;
    for (i = 0; i < 26; letters[i++] = 0);

    char r;
    for (i = 0; i < 26; i++) {
        /* Try each letter. */

        /* Seek to beginning of file. */
        rewind(fp);

        r = i + 'a';
        char c;
        while ((c = getc(fp)) != EOF) {
            polymerize_reject(c, r);
        }

        /* Count polymer length and purge stack. */
        letters[i] = stack_index - 1;
        printf("Polymer with %c exclusion is %d chars long.\n", i + 'a', letters[i]);

        purge();

        /* Check if this is the minimum. */
        if (letters[i] < min_length) {
            min_length = letters[i];
            min_letter = i + 'a';
        }

    }

    printf("Exclude %c to minimize polymer length = %d.\n", min_letter, min_length);
    return 0;
}
