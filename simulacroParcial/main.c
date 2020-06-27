#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

typedef struct
{
    int dia;
    int mes;
    int anio;
}eFecha;

typedef struct
{
    int idVuelo;
    int idAvion;
    int idPiloto;
    eFecha fecha;
    char destino[20];
    int cantPasajeros;
    int horaDespegue;
    int horaLlegada;
}eAvion;

int controller_loadFromText(char* path , LinkedList* pArrayListAvion);
int controller_saveAsText(char* path , LinkedList* pArrayListAvion);
int parser_AvionFromText(FILE* pFile , LinkedList* pArrayListAvion);
eAvion* avion_new();
eAvion* avion_newParametros(char* idVueloStr,char* idAvionStr,char* idPilotoStr, char* fechaStr, char* destinoStr,
                                char* cantPasajerosStr, char* horaDespegue, char* horaLlegada);
int avion_setIdVuelo(eAvion* this,int idVuelo);
int avion_setIdAvion(eAvion* this,int idAvion);
int avion_setIdPiloto(eAvion* this,int idPiloto);
int avion_setFecha(eAvion* this, eFecha fecha);
int avion_setDestino(eAvion* this,char* destino);
int avion_setCantPasajeros(eAvion* this,int cantPasajeros);
int avion_setHoraDespegue(eAvion* this,int horaDespegue);
int avion_setHoraLlegada(eAvion* this,int horaLlegada);
int mostrarAvion(eAvion* avion);
int mostrarAviones(LinkedList* lista);


int main()
{
    printf("Hello world!\n");
    return 0;
}


/** \brief Carga los datos de los aviones desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListAvion LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path , LinkedList* pArrayListAvion)
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
        r = parser_AvionFromText(f, pArrayListAvion);
    }

    fclose(f);

    return r;
}



/** \brief Guarda los datos de los aviones en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListAvion LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pArrayListAvion)
{

}



/** \brief Parsea los datos los datos de los aviones desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListAvion LinkedList*
 * \return int
 *
 */
int parser_AvionFromText(FILE* pFile , LinkedList* pArrayListAvion)
{
    int cant;
    int r = -1;
    char buffer[8][1500];
    eAvion* auxAvion;

    cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);

    while(!feof(pFile))
    {
        cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
        if(cant == 8)
        {
            auxAvion = avion_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7]);
            if(auxAvion != NULL)
            {
                ll_add(pArrayListAvion, auxAvion);
                r = 1;
            }
        }
    }

    if(r == 1)
    {
        printf("\nAviones cargados con exito!!\n");
    }
    else
    {
        printf("\nProblemas con el archivo\n");
    }

    return r;
}



/** \brief Crea un puntero a avion en la memoria dinamica y lo inicializa todo en 0 o "".
 *
 * \param eAvion* newAvion;
 * \param
 * \return newAvion;
 *
 */
eAvion* avion_new()
{
    eAvion* newAvion;
    newAvion = (eAvion*)malloc(sizeof(eAvion));

    if(newAvion != NULL)
    {
        newAvion->idVuelo = 0;
        newAvion->idAvion = 0;
        newAvion->idPiloto = 0;
        newAvion->fecha.dia = 0;
        newAvion->fecha.mes = 0;
        newAvion->fecha.anio = 0;
        strcpy(newAvion->destino, "");
        newAvion->cantPasajeros = 0;
        newAvion->horaDespegue = 0;
        newAvion->horaLlegada = 0;
    }

    return newAvion;
}



/** \brief Crea un puntero a avion y valida los datos.
 *
 * \param eAvion* newAvion;
 * \param
 * \return newAvion;
 *
 */
eAvion* avion_newParametros(char* idVueloStr, char* idAvionStr, char* idPilotoStr, char* fechaStr, char* destinoStr,
                                char* cantPasajerosStr, char* horaDespegue, char* horaLlegada)
{
    eAvion* newAvion;

    newAvion = avion_new();

    if(newAvion != NULL)
    {
        if(avion_setIdVuelo(newAvion, atoi(idVueloStr))
        || avion_setIdAvion(newAvion, atoi(idAvionStr))
        || avion_setIdPiloto(newAvion, atoi(idPilotoStr))
        || avion_setFecha(newAvion, fechaStr)
        || car_setAnio(newAvion, atoi(anioStr))
        || car_setColor(newAvion, colorStr)
        || car_setPrecio(newAvion, atof(precioStr)))
        {
            free(newAvion);
            newAvion = NULL;
        }
    }

    return newAvion;
}



int avion_setIdVuelo(eAvion* this,int idVuelo);
int avion_setIdAvion(eAvion* this,int idAvion);
int avion_setIdPiloto(eAvion* this,int idPiloto);
int avion_setFecha(eAvion* this, eFecha fecha);
int avion_setDestino(eAvion* this,char* destino);
int avion_setCantPasajeros(eAvion* this,int cantPasajeros);
int avion_setHoraDespegue(eAvion* this,int horaDespegue);
int avion_setHoraLlegada(eAvion* this,int horaLlegada);
int mostrarAvion(eAvion* avion);
int mostrarAviones(LinkedList* lista);

