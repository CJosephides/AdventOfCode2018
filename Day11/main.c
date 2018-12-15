#include <stdio.h>
#include <stdlib.h>
#define SIDE 300

/* Note argument (order): i = y; j = x. */
int power(int y, int x, int s)
{
    return ((((x + 10) * y + s) * (x + 10) / 100) % 10) - 5;
}

int power_square(int y, int x, int k, int grid[SIDE][SIDE], int s)
{
    int power_sum = 0;
    int i, j;
    for (i = y; i < y + k; i++) {
        for (j = x; j < x + k; j++) {
            power_sum += grid[i][j];
        }
    }
    return power_sum;
}

int main(int argc, char **argv)
{
    /* Requires a single argument: the grid serial number. */
    int serial = atoi(argv[1]);

    /* Initialize grid on the stack. */
    int grid[SIDE][SIDE];
    int i, j;
    for (i = 0; i < SIDE; i++) { 
        for (j = 0; j < SIDE; j++) {
            grid[i][j] = power(i, j, serial);
        }
    }

    /* Identify KxK square with highest power sum, for k in [1, 300]. */
    int k;
    int power_sum;
    int max_power = -1000;
    int max_i, max_j;
    int max_k;
    for (k = 1; k <= 300; k++) {
        for (i = 0; i <= SIDE - k; i++) {
            for (j = 0; j <= SIDE - k; j++) {
                power_sum = power_square(i, j, k, grid, serial);
                if (power_sum > max_power) {
                    max_i = i;
                    max_j = j;
                    max_k = k;
                    max_power = power_sum;
                }
            }
        }
        printf("Finished k = %d.\n", k);
        printf("X = %d, Y = %d, K = %d. Power = %d.\n", max_j, max_i, max_k, max_power);
    }

    return 0;
}
