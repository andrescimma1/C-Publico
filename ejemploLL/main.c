#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct
{
    int id;
    char marca[20];
    int anio;
    char color[20];
    float precio;
}eAuto;

int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int parser_CarFromText(FILE* pFile , LinkedList* pArrayListCar);
eAuto* car_new();
eAuto* car_newParametros(char* idStr,char* marcaStr,char* anio, char* colorStr, char* precioStr);
int car_setId(eAuto* this,int id);
int car_setMarca(eAuto* this,char* marca);
int car_setAnio(eAuto* this,int anio);
int car_setColor(eAuto* this,char* color);
int car_setPrecio(eAuto* this,float precio);
int mostrarAuto(eAuto* car);
int mostrarAutos(LinkedList* lista);
int filtrarxRangoAnio(void* unAuto);



int main()
{
    LinkedList* lista = ll_newLinkedList();
    LinkedList* listaFiltrada = NULL;

    if(lista == NULL)
    {
        printf("No se pudo conseguir memoria\n");
        exit(EXIT_FAILURE);
    }



    printf("Lista declarada!\n");

    // Leer archivos autos.csv y cargarlos en el LinkedList
    controller_loadFromText("autos.csv", lista);

    // Muestro los autos
    mostrarAutos(lista);

    // Hacer una nueva lista con los autos que estan entre el
    // anio 2000 y 2005


    //listaFiltrada = ll_clone(lista);

    listaFiltrada = ll_filter(lista, filtrarxRangoAnio);

    mostrarAutos(listaFiltrada);

    // Guardar la lista filtrada en un nuevo archivo .csv
    controller_saveAsText("autos2.csv", listaFiltrada);

    return 0;
}


/** \brief Carga los datos de los autos desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListCar LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListCar)
{
    int r = 1;
    FILE* f = fopen(path, "r");

    if(f == NULL)
    {
        printf("Problema al abrir el archivo\n");
        r = -1;
    }
    else
    {
        r = parser_CarFromText(f, pArrayListCar);
    }

    fclose(f);

    return r;
}


/** \brief Guarda los datos de los autos en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListCar LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListCar)
{
    int r = 1;
    int tam = ll_len(pArrayListCar);
    FILE* f;
    eAuto* auxCar;

    f = fopen(path, "w");

    if(f == NULL)
    {
        printf("Error al abrir el archivo\n\n");
    }
    else
    {
        fprintf(f, "id,marca,anio,color,precio\n");

        for(int i=0; i<tam; i++)
        {
            auxCar = (eAuto*)ll_get(pArrayListCar, i);
            fprintf(f, "%d,%s,%d,%s,%f \n", auxCar->id, auxCar->marca, auxCar->anio, auxCar->color, auxCar->precio);
            r = 1;
        }
    }

    if(r == 1)
    {
        printf("Se han guardado con exito!!\n\n");
    }

    fclose(f);

    return r;
}


/** \brief Parsea los datos los datos de los autos desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListCar LinkedList*
 * \return int
 *
 */
int parser_CarFromText(FILE* pFile , LinkedList* pArrayListCar)
{
    int cant;
    int r = -1;
    char buffer[5][1500];
    eAuto* auxCar;

    cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

    while(!feof(pFile))
    {
        cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
        if(cant == 5)
        {
            auxCar = car_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
            if(auxCar != NULL)
            {
                ll_add(pArrayListCar, auxCar);
                r = 1;
            }
        }
    }

    if(r == 1)
    {
        printf("\nEmpleados cargados con exito!!\n");
    }
    else
    {
        printf("\nProblemas con el archivo\n");
    }

    return r;
}


/** \brief Crea un puntero a auto en la memoria dinamica y lo inicializa todo en 0 o "".
 *
 * \param eAuto* newAuto;
 * \param
 * \return newAuto;
 *
 */
eAuto* car_new()
{
    eAuto* newAuto;
    newAuto = (eAuto*)malloc(sizeof(eAuto));

    if(newAuto != NULL)
    {
        newAuto->id = 0;
        strcpy(newAuto->marca, "");
        newAuto->anio = 0;
        strcpy(newAuto->color, "");
        newAuto->precio = 0;
    }

    return newAuto;
}



/** \brief Crea un puntero a auto y valida los datos.
 *
 * \param eAuto* newAuto;
 * \param
 * \return newAuto;
 *
 */
eAuto* car_newParametros(char* idStr,char* marcaStr,char* anioStr, char* colorStr, char* precioStr)
{
    eAuto* newAuto;

    newAuto = car_new();

    if(newAuto != NULL)
    {
        if(car_setId(newAuto, atoi(idStr))
        || car_setMarca(newAuto, marcaStr)
        || car_setAnio(newAuto, atoi(anioStr))
        || car_setColor(newAuto, colorStr)
        || car_setPrecio(newAuto, atof(precioStr)))
        {
            free(newAuto);
            newAuto = NULL;
        }
    }

    return newAuto;
}



/** \brief Valida el id puesto como segundo parámetro y se lo asigna al auto
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int car_setId(eAuto* this,int id)
{
    int error = 1;

    if(this != NULL && id >= 0 && id <= 20000)
    {
        this->id = id;
        error = 0;
    }

    return error;
}



/** \brief Valida la marca puesta como segundo parámetro y se lo asigna al auto
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int car_setMarca(eAuto* this,char* marca)
{
    int error = 1;

    if(this != NULL && strlen(marca) >= 3 && strlen(marca) < 20)
    {
        strcpy(this->marca, marca);
        error = 0;
    }

    return error;
}


/** \brief Valida el año puesto como segundo parámetro y se lo asigna al auto
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int car_setAnio(eAuto* this,int anio)
{
    int error = 1;

    if(this != NULL && anio >= 1 && anio <= 4000)
    {
        this->anio = anio;
        error = 0;
    }

    return error;
}



/** \brief Valida el color puesto como segundo parámetro y se lo asigna al auto
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int car_setColor(eAuto* this,char* color)
{
    int error = 1;

    if(this != NULL && strlen(color) >= 3 && strlen(color) < 20)
    {
        strcpy(this->color, color);
        error = 0;
    }

    return error;
}



/** \brief Valida el precio como segundo parámetro y se lo asigna al empleado
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int car_setPrecio(eAuto* this,float precio)
{
    int error = 1;

    if(this != NULL && precio >= 5000 && precio <= 100000)
    {
        this->precio = precio;
        error = 0;
    }

    return error;
}



/** \brief Muestra un autos
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int mostrarAuto(eAuto* car)
{
    int error = 1;

    if(car != NULL)
    {
        printf("%d  %10s     %d    %10s       %.2f\n", car->id, car->marca, car->anio, car->color, car->precio);
        error = 0;
    }

    return error;
}



/** \brief Muestra los autos de la lista.
 *
 * \param int r = -1;
 * \param int flag = 0;
 * \param int tam = ll_len(lista);
 * \param eAuto* auxAuto;
 * \return r;
 *
 */
int mostrarAutos(LinkedList* lista)
{
    int r = -1;
    int flag = 0;

    int tam = ll_len(lista); //Contiene el tamaño de la lista
    eAuto* auxAuto;

    if(lista != NULL)
    {
        printf("ID         MARCA    ANIO      COLOR     PRECIO\n");
        printf("------------------------------------------------\n");
        for(int i=0; i<tam; i++)
        {
            auxAuto = (eAuto*)ll_get(lista, i); //Mediante el indice obtiene la ubicacion del empleado
            if(auxAuto != NULL)
            {
                mostrarAuto(auxAuto);
                flag = 1;
            }
        }
        if(flag == 0)
        {
            printf("No hay autos para mostrar\n");
        }
        printf("\n\n");
        r = 1;
    }

    return r;
}


int filtrarxRangoAnio(void* unAuto)
{
    int auxReturn = 0;
    eAuto* x;

    if(unAuto != NULL)
    {
        x = (eAuto*)unAuto;

        if(x->anio >= 2000 && x->anio <= 2005)
        {
            auxReturn = 1;
        }
    }

    return auxReturn;
}
