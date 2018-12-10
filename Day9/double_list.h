#ifndef _H_DLI
#define _H_DLI

typedef struct dl_item {
    int x;
    int is_current;
    struct dl_item *next;
    struct dl_item *prev;
} DLI, *DLIPtr;

DLIPtr get_clockwise(DLIPtr dliptr, int n);
DLIPtr get_counterclockwise(DLIPtr dliptr, int n);
DLIPtr insert_marble(DLIPtr dliptr, int x);
void remove_marble(DLIPtr dliptr);
void print_marbles(DLIPtr dliptr);
void enable_current(DLIPtr dliptr);
void disable_current(DLIPtr dliptr);

#endif
