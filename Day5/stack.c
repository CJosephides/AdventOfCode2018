#include <stdio.h>
#define MAXSTACK 50000


/* This is our stack of characters. */
char stack[MAXSTACK];
int stack_index = 0;  // points to the next free position in the stack

/* Standard pop. */
char pop()
{
    if (stack_index > 0) {
        return stack[--stack_index];
    } else {
        return '\0';
    }
}


/* Standard insert. */
int insert(char x)
{
    if (stack_index < MAXSTACK) {
        stack[stack_index++] = x;
    } else {
        printf("Error: stack full.\n");
    }
    return stack_index;
}

/* Tailored stack operations. */

/* polymerize checks if the character to be inserted can annihilate 
 * the top character in the stack. */
int polymerize(char x)
{
    /* Boundary case: nothing in the stack. */
    if (stack_index == 0) {
        insert(x);
        return stack_index;
    }

    /* General case: one or more items in the stack. */
    char y = pop();
    if ((x != y + 32) && (x != y - 32)) {
        /* No annihilation. Put y back and insert x. */
        insert(y);
        insert(x);
    }
    /* Otherwise x annihilates y and we put neither back. */

    return stack_index;
}

/* dump prints the stack in reverse. */
int dump()
{
    int i;
    for (i = 0; i < stack_index; printf("%c", stack[i++]));
    printf("\n");

    return i - 1;  // because stack_index is one past the \0
}
