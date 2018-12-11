#include <stdio.h>
#include <stdlib.h>
#define LARGEINT 1000
#define MIN_X -1000
#define MAX_X 1000
#define MIN_Y -1000
#define MAX_Y 1000
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

typedef struct star {
    int x, y, v_x, v_y;
} Star, *StarPtr;

/* Update star positions by one tick. */
void update(Star **stars, int n_stars)
{
    int i;
    StarPtr star;
    for (i = 0; i < n_stars; i++) {
        star = stars[i];
        star->x += star->v_x;
        star->y += star->v_y;
    }
}

void stats(Star **stars, int n_stars)
{
    // First pass through stars to determine the rectangular bounds.
    int min_x = LARGEINT;
    int max_x = -LARGEINT;
    int min_y = LARGEINT;
    int max_y = -LARGEINT;

    int i;
    StarPtr star;
    for (i = 0; i < n_stars; i++) {
        star = stars[i];
        if (star->x < min_x)
            min_x = star->x;
        if (star->x > max_x)
            max_x = star->x;
        if (star->y < min_y)
            min_y = star->y;
        if (star->y > max_y)
            max_y = star->y;
    }

    printf("X in [%d, %d]; Y in [%d, %d].\n", min_x, max_x, min_y, max_y);
}

/* Print star positions to stdout. */
void display(Star **stars, int n_stars)
{

    // First pass through stars to determine the rectangular bounds.
    int min_x = LARGEINT;
    int max_x = -LARGEINT;
    int min_y = LARGEINT;
    int max_y = -LARGEINT;

    int i;
    StarPtr star;
    for (i = 0; i < n_stars; i++) {
        star = stars[i];
        if (star->x < min_x)
            min_x = star->x;
        if (star->x > max_x)
            max_x = star->x;
        if (star->y < min_y)
            min_y = star->y;
        if (star->y > max_y)
            max_y = star->y;
    }

    //min_x = max(min_x, MIN_X);
    //min_y = max(min_y, MIN_Y);
    //max_x = min(max_x, MAX_X);
    //max_y = min(max_y, MAX_Y);

    printf("X in [%d, %d]; Y in [%d, %d].\n", min_x, max_x, min_y, max_y);

    // Initialize rectangular array.
    int j;
    char rect[max_y - min_y + 1][max_x - min_x + 1];

    for (i = 0; i < (max_y - min_y) + 1; i++)
        for (j = 0; j < (max_x - min_x) + 1; j++)
            rect[i][j] = '.';

    // Mark stars.
    for (i = 0; i < n_stars; i++) {
        star = stars[i];
        
            if ((star->y >= min_y) && (star->y <= max_y) && (star->x >= min_x) && (star->x <= max_x))
                rect[star->y - min_y][star->x - min_x] = '#';
    }

    // Print.
    for (i = 0; i < (max_y - min_y) + 1; i++) {
        for (j = 0; j < (max_x - min_x) + 1; j++) {
            putc(rect[i][j], stdout);
        }
        putc('\n', stdout);
    }

    
}

int main(int argc, char **argv)
{

    /* Read file and count number of stars (lines). */
    FILE *fp = fopen(argv[1], "rb");
    int num_lines = 0;
    char c;

    while ((c = fgetc(fp)) != EOF)
        if (c == '\n')
            num_lines++;

    /* Allocate memory for stars and read file again. */
    rewind(fp);
    StarPtr stars[num_lines];

    int i, x, y, v_x, v_y;
    for (i = 0; i < num_lines; i++) {
        stars[i] = malloc(sizeof(Star));
        fscanf(fp, "position=<%d, %d> velocity=<%d, %d>\n", &x, &y, &v_x, &v_y);
        stars[i]->x = x; stars[i]->y = y; stars[i]->v_x = v_x; stars[i]->v_y = v_y;
        //printf("Identified star %d at (%d, %d), with velocity (%d, %d).\n", i, stars[i]->x, stars[i]->y, stars[i]->v_x, stars[i]->v_y);
    }

    // Update argv[2] frames.
    int t = 0;

    for (t = 0; t < atoi(argv[2]); t++) {
        printf("Tick = %d.\n", t);
        update(stars, num_lines);
        stats(stars, num_lines);
    }

    // Print frames from argv[2] to argv[3]
    for (t = atoi(argv[2]); t < atoi(argv[3]); t++) {
        printf("Tick = %d.\n", t);
        display(stars, num_lines);
        printf("\n");
        update(stars, num_lines);
    }


    return 0;
}
