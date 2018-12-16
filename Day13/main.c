#include "map.h"

/* Arguments:
 * 1. input file
 * 2. number of ticks to advance */
int main(int argc, char **argv)
{

    int i, j, k;

    /* Open input file. */
    FILE *fp = fopen(argv[1], "rb");

    /* Allocate memory for map... */
    char **map = calloc(MAPSIZE, sizeof(char *));
    for (i = 0; i < MAPSIZE; i++) {
        map[i] = calloc(MAPSIZE, sizeof(char));
        for (j = 0; j < MAPSIZE; map[i][j++] = '.');
    }

    /* .. and carts. */
    CartPtr *carts = calloc(MAXCART, sizeof(CartPtr));
    for (k = 0; k < MAXCART; k++) {
        carts[k] = NULL;
    }

    /* Read input: create map and carts. */
    read_input(fp, map, carts);
    //printf("Tick 0\n");
    //print_mapcarts(map, carts);

    for (i = 1; i < atoi(argv[2]); i++) {
        update(map, carts);
        printf("Tick %d\n", i);
        //print_mapcarts(map, carts);
    }

    return 0;
}
