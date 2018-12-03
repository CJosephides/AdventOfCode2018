#include <stdio.h>
#define BUF_SIZE 10000

int main(int argc, char **argv)
{
    /* Read entire input file to memory. */
    FILE *fp;
    fp = fopen("input.dat", "rb");
    char buffer[BUF_SIZE];

    fread(buffer, 1, BUF_SIZE, fp);
    
    /* Sum contents, line by line. */
    char *data = buffer;
    int offset, sum, f;
    while (sscanf(data, "%d%n", &f, &offset)==1) {
        sum += f;
        data += offset;
    }

    printf("%d\n", sum);
    return 0;
}
