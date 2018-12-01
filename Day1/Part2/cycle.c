#include <stdio.h>
#include <limits.h>
#define ARRSIZE 1000000
#define OFFSET ARRSIZE / 2

int main(int argc, char **argv)
{

    /* Read input from stdin into memory first. */
    int i;
    int input[1000];
    for (i=0; i < 1000; scanf("%d", &input[i++]));

    /* Cycle through the input. */
    char visited_frequencies[ARRSIZE];
    int sum, f = 0;
    i = 0;
    while (1) {
        sum += input[(i++) % 1000];  // overflows yada yada
        if (visited_frequencies[OFFSET + sum]) {
            printf("Duplicate found = %d\n", sum);
            break;
        } else {
            visited_frequencies[OFFSET + sum] = 1;
        }
    }

    return 0;
}
