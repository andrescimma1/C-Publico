#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char nombre[20];
    char sexo;
    float sueldo;
}eEmpleado;

int empleadoSetId(eEmpleado* empleado, int id);
int empleadoSetNombre(eEmpleado* empleado, char* nombre);
int empleadoSetSexo(eEmpleado* empleado, char sexo);
int empleadoSetSueldo(eEmpleado* empleado, float sueldo);

int empleadoGetId(int* pId, eEmpleado* empleado);
int empleadoGetNombre(char* pNombre, eEmpleado* empleado);
int empleadoGetSexo(char* pSexo, eEmpleado* empleado);
int empleadoGetSueldo(float* pSueldo, eEmpleado* empleado);

eEmpleado* new_Empleado();
eEmpleado* new_EmpleadoParam(char* id, char* nombre, char* sexo, char* sueldo);


int main()
{
    //int id;
    //char nombre[20];
    //char sexo;
    //float sueldo;
    char buffer[4][100];

    eEmpleado* auxEmpleado;

    int cant;

    FILE* f;

    f = fopen("empleadosConEncabezado.txt", "r");

    if(f == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    fscanf(f, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]); //Lectura fantasma para leer el encabezado
    printf("%s  %s  %s  %s\n\n", buffer[0], buffer[1], buffer[2], buffer[3]);

    while(!feof(f))
    {
        cant = fscanf(f, "%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);

        //printf("%d\n", cant);
        if(cant == 4)
        {
            auxEmpleado = new_EmpleadoParam(buffer[0], buffer[1], buffer[2], buffer[3]);
            printf("%d %s %c %.2f\n", auxEmpleado->id, auxEmpleado->nombre, auxEmpleado->sexo, auxEmpleado->sueldo);
        }
        else
        {
            break;
        }
    }


    fclose(f);

    return 0;
}


eEmpleado* new_Empleado()
{
    eEmpleado* nuevoEmpleado;
    nuevoEmpleado = (eEmpleado*)malloc(sizeof(eEmpleado));

    if(nuevoEmpleado != NULL)
    {
        nuevoEmpleado->id = 0;
        strcpy(nuevoEmpleado->nombre, "");
        nuevoEmpleado->sexo = ' ';
        nuevoEmpleado->sueldo = 0;
    }

    return nuevoEmpleado;
}

eEmpleado* new_EmpleadoParam(char* id, char* nombre, char* sexo, char* sueldo)
{
    eEmpleado* nuevoEmpleado;

    nuevoEmpleado = new_Empleado();

    if(nuevoEmpleado != NULL)
    {
        if(empleadoSetId(nuevoEmpleado, atoi(id))  //Lo casteo a int
        || empleadoSetNombre(nuevoEmpleado, nombre)
        || empleadoSetSexo(nuevoEmpleado, sexo[0])  //Le doy el primer indice ya que el char lleva una sola letra
        || empleadoSetSueldo(nuevoEmpleado, atof(sueldo)))  //Lo casteo a float
        {
            free(nuevoEmpleado);
            nuevoEmpleado = NULL;
        }
    }

    return nuevoEmpleado;
}


int empleadoSetId(eEmpleado* empleado, int id)
{
    int error = 1;

    if(empleado != NULL)
    {
        empleado->id = id;
        error = 0;
    }

    return error;
}

int empleadoSetNombre(eEmpleado* empleado, char* nombre)
{
    int error = 1;

    if(empleado != NULL)
    {
        strcpy(empleado->nombre, nombre);
        error = 0;
    }

    return error;
}

int empleadoSetSexo(eEmpleado* empleado, char sexo)
{
    int error = 1;

    if(empleado != NULL)
    {
        empleado->sexo = sexo;
        error = 0;
    }

    return error;
}

int empleadoSetSueldo(eEmpleado* empleado, float sueldo)
{
    int error = 1;

    if(empleado != NULL)
    {
        empleado->sueldo = sueldo;
        error = 0;
    }

    return error;
}

int empleadoGetId(int* pId, eEmpleado* empleado)
{
    int error = 1;

    if(empleado != NULL && pId != NULL)
    {
        *pId = empleado->id;
        error = 0;
    }

    return error;
}


int empleadoGetNombre(char* pNombre, eEmpleado* empleado)
{
    int error = 1;

    if(empleado != NULL && pNombre != NULL)
    {
        strcpy(pNombre, empleado->nombre);
        error = 0;
    }

    return error;
}


int empleadoGetSexo(char* pSexo, eEmpleado* empleado)
{
    int error = 1;

    if(empleado != NULL && pSexo != NULL)
    {
        *pSexo = empleado->sexo;
        error = 0;
    }

    return error;
}

int empleadoGetSueldo(float* pSueldo, eEmpleado* empleado)
{
    int error = 1;

    if(empleado != NULL && pSueldo != NULL)
    {
        *pSueldo = empleado->sueldo;
        error = 0;
    }

    return error;
}
