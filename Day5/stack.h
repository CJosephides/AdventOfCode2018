#ifndef _STACK_H
#define _STACK_H

extern char *stack;
extern int stack_index;
char pop();
int insert(char x);
int polymerize(char x);
int polymerize_reject(char x, char r);
int dump();
void purge();

#endif

