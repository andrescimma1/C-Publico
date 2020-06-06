#include <stdio.h>
#include <stdlib.h>

int main()
{
    int* vec;

    vec = (int*)calloc(5, sizeof(int)); //Crea espacio en memoria dinamica e inicializa cada elemento en 0

    for(int i = 0; i < 5; i++)
    {
        printf("%d", *(vec + i));
    }
    return 0;
}
