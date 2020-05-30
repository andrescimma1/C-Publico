#include <stdio.h>
#include <stdlib.h>

void mostrarVector(int x[], int tam);
void mostrarVectorP(int* x, int tam);

int main()
{
    int vec[5] = {4, 7, 9, 4, 5};

    mostrarVector(vec, 5);

    printf("\n\n");

    mostrarVectorP(vec, 5);

    printf("\n\n");

    printf("%d\n", vec[0]); //Notación vectorial
    printf("%d\n", *(vec + 0)); //Notación de puntero



    return 0;
}


void mostrarVector(int x[], int tam)
{
    for(int i=0; i<tam; i++)
    {
        printf("%d ", x[i]);
    }
}


void mostrarVectorP(int* x, int tam)
{
    for(int i=0; i<tam; i++)
    {
        printf("%d ", *(x + i));
    }
}


