#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char nombre[20];
    int edad;
    float peso;
}ePersona;

int main()
{
    char c;
    char cadena[100];

    //ePersona per = {"Juan", 20, 80.7};
/*  FILE* f = fopen("archivo.txt", "w");

    if(f == NULL)
    {
        printf("Problemas para abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    //int x = 1234;

    fprintf(f, "Hola mundo");
    //fwrite(&x, sizeof(int), 1, f);

    fclose(f);*/

//--------------------------------------------------------------------------------
    FILE* f = fopen("archivo.txt", "r");

    if(f == NULL)
    {
        printf("Problemas para abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(f))
    {
        //c = fgetc(f);
        //printf("%c", c);
        fgets(cadena, 100, f);
        printf("%s", cadena);
    }

    fclose(f);

//--------------------------------------------------------------------------------
/*  FILE* f = fopen("archivo.bin", "wb");

    if(f == NULL)
    {
        printf("Problemas para abrir el archivo\n");
    }

    fwrite(&per, sizeof(ePersona), 1, f);

    fclose(f);*/


//--------------------------------------------------------------------------------
    f = fopen("archivo.bin", "rb");

    ePersona per;

    if(f == NULL)
    {
        printf("Problemas para abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    fread(&per, sizeof(ePersona), 1, f);

    printf("\nNombre: %s Edad: %d Peso: %.2f\n", per.nombre, per.edad, per.peso);

    return 0;
}
