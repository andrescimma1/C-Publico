#include <stdio.h>
#include <stdlib.h>

void swapear(int* a, int* b);

int main()
{
    int x = 4;
    int y = 6;

    printf("x: %d y: %d\n", x, y);

    swapear(&x, &y);

    printf("x: %d y: %d\n", x, y);
    return 0;
}



void swapear(int* a, int* b)
{
    int aux;

    aux = *a;
    *a = *b;
    *b = aux;
}
