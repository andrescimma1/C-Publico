#include <stdio.h>
#include <stdlib.h>

int main()
{
    int* vectorDinamico;
    int* auxiliar;

    vectorDinamico = (int*)malloc(5 * sizeof(int));

    for(int i = 0; i < 5; i++)
    {
        printf("Ingrese un numero: ");
        scanf("%d", (vectorDinamico + i));
    }

    for(int i = 0; i < 5; i++)
    {
        printf("%d ", *(vectorDinamico + i));
    }

    auxiliar = (int*)realloc(vectorDinamico, 10 * sizeof(int)); //Agrando el vector
    if(auxiliar != NULL)
    {
        vectorDinamico = auxiliar;
        printf("Se pudo agrandar el tamanio del vector\n");
    }
    else
    {
        printf("No se encontro espacio en la memoria\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 5; i < 10; i++)
    {
        printf("Ingrese numero: ");
        scanf("%d", (vectorDinamico + i));
    }

    for(int i = 0; i < 10; i++)
    {
        printf("%d", *(vectorDinamico + i));
    }

    free(vectorDinamico);
    return 0;
}
