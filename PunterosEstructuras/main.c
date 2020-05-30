#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int dia;
    int mes;
    int anio;
}eFecha;

typedef struct
{
    int id;
    char nombre[20];
    float sueldo;
    eFecha fechaIngreso;
}eEmpleado;

void cargarEstructura(eEmpleado* p);

int main()
{
    eEmpleado emp = {1234, "Juan", 45000, {29, 5, 2020}};

    cargarEstructura(&emp);

    //eEmpleado* emp2 = (eEmpleado*)malloc(sizeof(eEmpleado));

    printf("%d %s %.2f %d/%d/%d\n", emp.id, emp.nombre, emp.sueldo, emp.fechaIngreso.dia, emp.fechaIngreso.mes, emp.fechaIngreso.anio);


    return 0;
}


void cargarEstructura(eEmpleado* p)
{
    printf("Ingrese id: ");
    scanf("%d", &p->id);

    printf("Ingrese nombre: ");
    fflush(stdin);
    gets(p->nombre);

}
