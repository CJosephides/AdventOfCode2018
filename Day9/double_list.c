#include "double_list.h"
#include <stdio.h>
#include <stdlib.h>

/* Get the DLI n marbles clockwise of the DLI pointed to by dliptr. */
DLIPtr get_clockwise(DLIPtr dliptr, int n)
{

    if (dliptr == NULL)
        return NULL;

    int i;
    for (i = 0; i < n; i++)
            dliptr = dliptr->next;

    return dliptr;
}

/* Get the DLI n marbles counter-clockwise of the DLI pointed to by dliptr. */
DLIPtr get_counterclockwise(DLIPtr dliptr, int n)
{

    if (dliptr == NULL)
        return NULL;

    int i;
    for (i = 0; i < n; i++) 
        dliptr = dliptr->prev;
    return dliptr;

}

/* Insert marble, with number x, in the place of the marble pointed to by DLIPtr and 
 * shift the one already there clockwise. If DLIPtr is the null pointer, then initialize a new
 * doubly-linked list. Also designates as current marble. */
DLIPtr insert_marble(DLIPtr dliptr, int x)
{

    DLIPtr new_dliptr = malloc(sizeof(DLI));
    new_dliptr->x = x;
    new_dliptr->is_current = 0;

    if (dliptr == NULL) {
        new_dliptr->next = new_dliptr;
        new_dliptr->prev = new_dliptr;
        return new_dliptr;
    }

    DLIPtr ccw_of_dliptr = dliptr->prev;

    ccw_of_dliptr->next = new_dliptr;
    new_dliptr->prev = ccw_of_dliptr;
    new_dliptr->next = dliptr;
    dliptr->prev = new_dliptr;

    return new_dliptr;
}

void remove_marble(DLIPtr dliptr)
{
    DLIPtr ccw = dliptr->prev;
    DLIPtr cw = dliptr->next;
    ccw->next = cw;
    cw->prev = ccw;
    free(dliptr); 
}

void disable_current(DLIPtr dliptr)
{
    if (dliptr != NULL)
        dliptr->is_current = 0;
}

void enable_current(DLIPtr dliptr)
{
    if (dliptr != NULL)
        dliptr->is_current = 1;
}

void print_marbles(DLIPtr dliptr)
{

    DLIPtr root = dliptr;
    
    /* Print root. */
    if (root->is_current == 1) {
        printf("*");
    }
    printf("%d ", dliptr->x);
    dliptr = dliptr->next;


    /* Main loop. */
    while (dliptr != root) {
        if (dliptr->is_current == 1) {
            printf("*");
        }
        printf("%d ", dliptr->x);
        dliptr = dliptr->next;
    }
    printf("\n");
}
