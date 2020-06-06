#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombre[20];
    char sexo;
    float peso;
}eEmpleado;

int mostrarEmpleado(eEmpleado* unEmpleado);

int main()
{
    eEmpleado* emp1;
    emp1 = (eEmpleado*)malloc(sizeof(eEmpleado));
    if(emp1 == NULL)
    {
        printf("No se consiguio memoria\n");
        exit(EXIT_FAILURE);
    }
    emp1->id = 1234;
    strcpy(emp1->nombre, "Jose");
    emp1->sexo = 'm';
    emp1->peso = 80.5;

    mostrarEmpleado(emp1);

    free(emp1);
    return 0;
}

int mostrarEmpleado(eEmpleado* unEmpleado)
{
    int todoOk = 0;

    if(unEmpleado != NULL)
    {
        todoOk = 1;
        printf("ID: %d Nombre: %s Sexo: %c Peso: %.2f", unEmpleado->id, unEmpleado->nombre, unEmpleado->sexo, unEmpleado->peso);
    }

    return todoOk;
}
