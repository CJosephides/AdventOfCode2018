#include <stdio.h>
#include <stdlib.h>
#define SIDE 300

/* Note argument (order): i = y; j = x. */
int power(int y, int x, int s)
{
    return ((((x + 10) * y + s) * (x + 10) / 100) % 10) - 5;
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

    /* Identify 3x3 square with highest power sum. */
    int power_sum;
    int max_power = -1000;
    int max_i, max_j;

    for (i = 0; i < SIDE - 2; i++) {
        for (j = 0; j < SIDE - 2; j++) {
            power_sum =  0;
            power_sum += power(i, j, serial);
            power_sum += power(i, j+1, serial);
            power_sum += power(i, j+2, serial);
            power_sum += power(i+1, j, serial);
            power_sum += power(i+1, j+1, serial);
            power_sum += power(i+1, j+2, serial);
            power_sum += power(i+2, j, serial);
            power_sum += power(i+2, j+1, serial);
            power_sum += power(i+2, j+2, serial);
            if (power_sum > max_power) {
                max_power = power_sum;
                max_i = i;
                max_j = j;
            }
        }
    }

    printf("Maximum 3x3 power square @ X=%d, Y=%d (power = %d).\n", max_j, max_i, max_power);

    return 0;
}
