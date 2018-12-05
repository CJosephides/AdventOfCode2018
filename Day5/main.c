#include <stdio.h>
#include "stack.h"

int main(int argc, char **argv)
{

    char c;
    while ((c = getc(stdin)) != EOF) {
        polymerize(c);
    }

    int polymer_size;
    polymer_size = dump();
    printf("Polymer size = %d.\n", polymer_size);

    return 0;
}
