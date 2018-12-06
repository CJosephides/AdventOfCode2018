#include <stdio.h>
#include <stdlib.h>
#include "manhattan.h"
#define INPUTSIZE 50
#define LARGE_INT 99999
#define MAX_TOTAL_DISTANCE 10000

/* Array to hold the coordinates of our elements. */
Point elements[INPUTSIZE]; 

/* Scan input and store positions, and assign IDs, to our points.
 * Also mark the edges of the smallest rectangle that contains our points. */
int scan_input(int *top, int *bottom, int *left, int *right)
{
    int y, x, id = 0;
    while (fscanf(stdin, "%d, %d", &x, &y) == 2) {
        elements[id].x = x;
        if (x > *right) {
            *right = x;
        }
        if (x < *left) {
            *left = x;
        }
        elements[id].y = y;
        if (y > *top) {
            *top = y;
        }
        if (y < *bottom) {
            *bottom = y;
        }
        elements[id].id = id;
        id++;
    }
    printf("Scanned %d elements.\nTop = %d; bottom = %d. Left = %d; right = %d.\n", id, *top, *bottom, *left, *right);
    return id;
}

int manhattan_distance(int x_0, int y_0, int x_1, int y_1)
{
    return abs(x_1 - x_0) + abs(y_1 - y_0);
}

/* Find the nearest element, from the elements array, for the point at (x, y)
 * Returns -1 if there is a tie for minimum distance.
 * Brute-force approach. It will be nice to optimize this to use a binary tree. */
int find_nearest_element(int x, int y)
{
    int id, min_id;
    int distances[INPUTSIZE];
    int min_distance = LARGE_INT;

    for (id = 0; id < INPUTSIZE; id++) {
        distances[id] = manhattan_distance(x, y, elements[id].x, elements[id].y);
        if (distances[id] < min_distance) {
            min_distance = distances[id];
            min_id = id;
        }
    }

    /* Check if we have a tie for minimum distance. */
    for (id = 0; id < INPUTSIZE; id++) {
        if (id != min_id && distances[id] == min_distance) {
            return -1;
        }
    }
    return min_id;
}

/* Return the sum of the Manhattan distances to all elements from (x, y). */
int sum_all_distances(int x, int y)
{
    int id, sum = 0;
    for (id = 0; id < INPUTSIZE; id++)
        sum += manhattan_distance(x, y, elements[id].x, elements[id].y);

    return sum;
}


int main(int argc, char **argv)
{

    /* Scan the input. */
    int top = -LARGE_INT, bottom = LARGE_INT, left = LARGE_INT, right = -LARGE_INT;    
    scan_input(&top, &bottom, &left, &right);

    /* Allocate a 2D array representing the bounding rectangle. */
    int i, j;
    int rectangle[top - bottom + 1][right - left + 1];
    for (i = 0; i <= (top - bottom); i++)
        for (j = 0; j <= (right - left); rectangle[i][j++] = -1);

    /* Iterate through the rectangle and mark nearest elements.
     * Keep a running tally as well. */
    int id, counts[INPUTSIZE];
    for (i = 0; i < INPUTSIZE; counts[i++] = 0);

    for (i = 0; i <= (top - bottom); i++)
        for (j = 0; j <= (right - left); j++) {
            id = find_nearest_element(left + j, bottom + i);
            rectangle[i][j] = id;
            if (id != -1) {
                counts[id]++;
            }
        }

    /* Exclude all elements that are nearest-points on the boundary. */
    int excluded[INPUTSIZE];
    for (i = 0; i < INPUTSIZE; excluded[i++] = 0);

    i = 0;
    for (j = 0; j <= (right - left); j++) {
        excluded[rectangle[i][j]] = 1;
    }
    i = top - bottom;
    for (j = 0; j <= (right - left); j++) {
        excluded[rectangle[i][j]] = 1;
    }
    j = 0;
    for (i = 0; i <= (top - bottom); i++) {
        excluded[rectangle[i][j]] = 1;
    }
    j = right - left;
    for (i = 0; i <= (top - bottom); i++) {
        excluded[rectangle[i][j]] = 1;
    }
    
    // Find largest finite area.
    int max_area = 0;
    for (i = 0; i < INPUTSIZE; i++) {
        if (counts[i] > max_area && excluded[i] == 0) {
            max_area = counts[i];
        }
    }
    printf("The largest finite area is %d.\n", max_area);

    /* Part 2. */
    
    /* Iterate through the rectangle, marking total distances.
     * Keep a count of all points with total distance < threshold. */

    int total_distances, num_valid = 0;
    for (i = 0; i <= (top - bottom); i++)
        for (j = 0; j <= (right - left); rectangle[i][j++] = -1);

    for (i = 0; i <= (top - bottom); i++) {
        for (j = 0; j <= (right - left); j++) {
            total_distances = sum_all_distances(left + j, bottom + i);
            if (total_distances < MAX_TOTAL_DISTANCE)
                num_valid++;
        }
    }

    /* This is the accepted answer, but I think it is wrong. */
            
    printf("The number of valid coordinates is %d.\n", num_valid);

    return 0;
}
