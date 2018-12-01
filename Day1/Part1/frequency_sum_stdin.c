#include <stdio.h>

int main()
{

    int f, sum = 0;
    while (scanf("%d", &f) == 1) sum += f;
    printf("frequency sum = %d\n", sum);
    return 0;

}
