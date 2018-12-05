#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#define INPUTSIZE 1143
#define MAXLINE 50
#define MAXGUARDS 4000

/* String comparison predicate for sorting
 * an array of strings. */
int strcmp_wrapper(const void *x, const void *y)
{
    return strcmp(*((char **) x), *((char**) y));
}

int main(int argc, char **argv)
{
    /* Read input from stdin into memory. */
    char **lines = calloc(INPUTSIZE, sizeof(char *));

    int i;
    char buffer[MAXLINE];
    for (i = 0; fgets(buffer, MAXLINE, stdin) != NULL; i++) {
        lines[i] = malloc(MAXLINE * sizeof(char));
        strcpy(lines[i], buffer);
        printf("(%d) Read: %s", i, lines[i]);
    }

    /* Sort the input (lexicographically will do, I hope). */
    qsort(lines, INPUTSIZE, sizeof(char *), strcmp_wrapper);

    /* Check. */
    for (i = 0; i < INPUTSIZE; i++) {
        printf("(%d) Sorted: %s", i, lines[i]);
    }

    /* Walk through the sorted array. We will
     * keep an int sleeps[60] array for each guard, where
     * the ith element is a count of the number of times
     * that guard has been asleep for that minute during
     * the midnight hour. */
    int j;
    Guardptr *guards = calloc(MAXGUARDS, sizeof(Guardptr));
    for (i = 0; i < MAXGUARDS; i++) {
        guards[i] = malloc(sizeof(Guard));
        guards[i]->id = i;
        for (j = 0; j < 60; guards[i]->sleeps[j++] = 0); 
    }

    int guard_id;
    char status[50];
    int minute;
    int sleep_minute;
    int wake_minute;
    char *sleep_status = "falls";
    char *wake_status = "wakes";
    for (i = 0; i < INPUTSIZE; i++) {
        if (sscanf(lines[i], "[%*d-%*d-%*d %*d:%*d] Guard #%d begins", &guard_id) == 1) {
            /* Try to match the "begins" pattern. */
            printf("Guard #%d begins.\n", guard_id);
            continue;  // keep guard_id
        } else if (sscanf(lines[i], "[%*d-%*d-%*d 00:%d] %s", &minute, status) == 2) {
            if (strcmp(status, sleep_status) == 0) {
                sleep_minute = minute;
                printf("Guard #%d sleeps at %d.\n", guard_id, sleep_minute);
                continue;
            } else if (strcmp(status, wake_status) == 0) {
                wake_minute = minute;
                printf("Guard #%d wakes at %d.\n", guard_id, wake_minute);
                for (j = sleep_minute; j < wake_minute; guards[guard_id]->sleeps[j++]++);
                continue;
            } else {
                printf("%s\n", lines[i]);
                exit(1);
            }
        }
    }

    /* Find the maximum number of minutes sleep amongst all guards.
     * Also determine the most soporific minute for the sleepiest guard. */
    int max_guard_id;
    int max_sleep = 0;
    int total_sleep;
    int k;
    int sleepiest_minute;
    int sleepiest_minute_sleeps;
    for (i = 0; i < MAXGUARDS; i++) {
        total_sleep = 0;
        printf("(%d) Guard #%d sleeps:\n", i, guards[i]->id);
        for (k = 0; k < 60; printf("%d", guards[i]->sleeps[k++]));
        for (k = 0; k < 60; total_sleep += guards[i]->sleeps[k++]);
        printf("Guard %d total sleep = %d.\n", guards[i]->id, total_sleep);
        if (total_sleep > max_sleep) {
            max_sleep = total_sleep;
            max_guard_id = guards[i]->id;
        }
    }
    printf("Sleepiest guard is %d.\n", max_guard_id);

    sleepiest_minute_sleeps = 0;
    for (k = 0; k < 60; k++) {
        if (guards[max_guard_id]->sleeps[k] > sleepiest_minute_sleeps) {
            sleepiest_minute_sleeps = guards[max_guard_id]->sleeps[k];
            sleepiest_minute = k;
        }
    }
    printf("Sleepiest minute is %d.\n", sleepiest_minute);

    /* Clear up. */
    for (i = 0; i < INPUTSIZE; free(lines[i++]));
    free(lines);

    return 0;
}

