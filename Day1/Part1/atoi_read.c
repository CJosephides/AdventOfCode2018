#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUF_SIZE 10000

int main(int argc, char **argv)
{
    /* Read entire input file to memory. */
    FILE *fp;
    fp = fopen("input.dat", "rb");
    char buffer[BUF_SIZE];

    fread(buffer, 1, BUF_SIZE, fp);

    /* Tokenize string and sum tokens. */
    char *token;
    int sum;
    token = strtok(buffer, "\n");

    while (token != NULL) {
        sum += atoi(token);
        token = strtok(NULL, "\n");
    }

    printf("sum = %d\n", sum);
    return 0;
}
