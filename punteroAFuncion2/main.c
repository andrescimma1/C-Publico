#include <stdio.h>
#include <stdlib.h>

int sumar(int a, int b);
int restar(int a, int b);
int multiplicar(int a, int b);
int calcular(int a, int b, int(*callback)(int, int));

int main()
{
    printf("El resultado es %d", calcular(4, 5, multiplicar));
    return 0;
}

int sumar(int a, int b)
{
    return a + b;
}

int restar(int a, int b)
{
    return a - b;
}

int multiplicar(int a, int b)
{
    return a * b;
}

int calcular(int a, int b, int(*callback)(int, int))
{
    return callback(a, b);
}
