#include <stdio.h>
#include <stdlib.h>

int main()
{
    int xEstatica;

    int* xDinamica = (int*)malloc(sizeof(int));

    printf("Dame un valor para la variable estatica: ");
    scanf("%d", &xEstatica);

    printf("Dame un valor para la variable dinamica: ");
    scanf("%d", xDinamica);

    printf("El valor de la variable estatica es %d \n", xEstatica);
    printf("El valor de la variable dinamica es %d \n", *xDinamica);
    return 0;
}
