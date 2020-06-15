#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char nombre[20];
    char sexo;
    float sueldo;
}eEmpleado;

int main()
{
    eEmpleado emp = {1234, "Jose", 'm', 38300};

    FILE* f = fopen("datos.txt", "wb");

    if(f == NULL)
    {
        printf("No se pudo abrir el archivo\n");
        exit(EXIT_FAILURE);
    }

    //fwrite(&emp, sizeof(eEmpleado), 1, f);
    //fprintf(f, "%d %s %c %.2f", emp.id, emp.nombre, emp.sexo, emp.sueldo);
    fread(&emp, sizeof(eEmpleado), 1, f);

    fclose(f);

    printf("%d %s %c %.2f", emp.id, emp.nombre, emp.sexo, emp.sueldo);

    return 0;
}
