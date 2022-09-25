#include <stdio.h>
#include <stdlib.h>
void allocArray(int ***p, int m, int n)
{
    *p = (int **) malloc(sizeof(int *) * m);
    (*p)[0] = malloc(sizeof(int) * m * n);
    for (int i=1; i<m; i++) {
        (*p)[i] = (*p)[0] + n * i;
    }
}

int main()
{
    int **array, *a;
    int j, k;
    allocArray(&array, 5, 10);
    for(j = 0;j < 5;j ++)
        for(k = 0;k < 10;k ++)
            array[j][k] = j * 10 + k;
        for(j = 0;j < 5;j ++)
            for(k = 0;k < 10;k ++)
                printf("%p ", &(array[j][k]));
}
