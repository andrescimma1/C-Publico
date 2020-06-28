#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#define TAMPILOTOS 5

typedef struct
{
    int id;
    char nombre[20];
}ePiloto;

typedef struct
{
    int idVuelo;
    int idAvion;
    int idPiloto;
    int dia;
    int mes;
    int anio;
    char destino[20];
    int cantPasajeros;
    int horaDespegue;
    int horaLlegada;
}eAvion;

int controller_loadFromText(char* path , LinkedList* pArrayListAvion);
int controller_saveAsText(char* path , LinkedList* pArrayListAvion);
int parser_AvionFromText(FILE* pFile , LinkedList* pArrayListAvion);
eAvion* avion_new();
eAvion* avion_newParametros(char* idVueloStr,char* idAvionStr,char* idPilotoStr, char* diaStr, char* mesStr, char* anioStr, char* destinoStr,
                                char* cantPasajerosStr, char* horaDespegue, char* horaLlegada);
int avion_setIdVuelo(eAvion* this,int idVuelo);
int avion_setIdAvion(eAvion* this,int idAvion);
int avion_setIdPiloto(eAvion* this,int idPiloto);
int avion_setDia(eAvion* this, int dia);
int avion_setMes(eAvion* this, int mes);
int avion_setAnio(eAvion* this, int anio);
int avion_setDestino(eAvion* this,char* destino);
int avion_setCantPasajeros(eAvion* this,int cantPasajeros);
int avion_setHoraDespegue(eAvion* this,int horaDespegue);
int avion_setHoraLlegada(eAvion* this,int horaLlegada);
int mostrarAvion(eAvion* avion, LinkedList* listaPilotos);
int mostrarAviones(LinkedList* lista, LinkedList* listaPilotos);
int menu();
void cantidadTotalPasajeros(LinkedList* lista);
void cantidadPasajerosIrlanda(LinkedList* lista);
void vuelosAPortugal(LinkedList* lista, LinkedList* listaPilotos);
int filtrarxVuelosCortos(void* unAvion);
int filtrarSinAlexLifeson(void* unAvion);


int main()
{
    //ePiloto pilotos[] = {{1, "Alex Lifeson"}, {2, "Richard Bach"}, {3, "John Kerry"}, {4, "Erwin Rommel"}, {5, "Stephen Coonts"}};

    LinkedList* listaPilotos;

    listaPilotos = ll_newLinkedList();

    ePiloto* auxPiloto;


    if(listaPilotos != NULL)
    {
        for(int i=0; i<TAMPILOTOS; i++)
        {
            auxPiloto = (ePiloto*)malloc(sizeof(ePiloto));

            if(auxPiloto != NULL)
            {
                if(i == 0)
                {
                    auxPiloto->id = 1;
                    strcpy(auxPiloto->nombre, "Alex Lifeson");
                    ll_add(listaPilotos, auxPiloto);
                }
                if(i == 1)
                {
                    auxPiloto->id = 2;
                    strcpy(auxPiloto->nombre, "Richard Bach");
                    ll_add(listaPilotos, auxPiloto);
                }
                if(i == 2)
                {
                    auxPiloto->id = 3;
                    strcpy(auxPiloto->nombre, "John Kerry");
                    ll_add(listaPilotos, auxPiloto);
                }
                if(i == 3)
                {
                    auxPiloto->id = 4;
                    strcpy(auxPiloto->nombre, "Erwin Rommel");
                    ll_add(listaPilotos, auxPiloto);
                }
                if(i == 4)
                {
                    auxPiloto->id = 5;
                    strcpy(auxPiloto->nombre, "Stephen Coonts");
                    ll_add(listaPilotos, auxPiloto);
                }
            }
        }
    }

    LinkedList* lista;
    char seguir;
    char archivo[20];
    int r;

    lista = ll_newLinkedList();

    LinkedList* listaVuelosCortos;
    LinkedList* listaAlexLifeson;

    do
    {
        switch(menu())
        {
            case 1: printf("\nIngrese el nombre del archivo que desea cargar (Ej: Vuelos.csv): ");
                    fflush(stdin);
                    gets(archivo);
                    r = controller_loadFromText(archivo, lista);
                    if(r == -1)
                    {
                        printf("No se pudo leer el archivo\n\n");
                        exit(EXIT_FAILURE);
                    }
                    break;

            case 2: mostrarAviones(lista, listaPilotos);
                    break;

            case 3: cantidadTotalPasajeros(lista);
                    break;

            case 4: cantidadPasajerosIrlanda(lista);
                    break;

            case 5: listaVuelosCortos = ll_newLinkedList();
                    listaVuelosCortos = ll_filter(lista, filtrarxVuelosCortos);
                    mostrarAviones(listaVuelosCortos, listaPilotos);
                    controller_saveAsText("VuelosCortos.csv", listaVuelosCortos);
                    break;

            case 6: vuelosAPortugal(lista, listaPilotos);
                    break;

            case 7: listaAlexLifeson = ll_newLinkedList();
                    listaAlexLifeson = ll_filter(lista, filtrarSinAlexLifeson);
                    mostrarAviones(listaAlexLifeson, listaPilotos);
                    controller_saveAsText("VuelosSinAlex.csv", listaAlexLifeson);
                    printf("\nNo te queremos Alex!\n\n");
                    break;

            case 8: printf("Seguro que desea salir? s/n: ");
                    fflush(stdin);
                    scanf("%c", &seguir);
                    break;

            default: printf("Error, opcion incorrecta\n\n");
                     break;

        }
    }while(seguir != 's');

    ll_deleteLinkedList(lista);
    ll_deleteLinkedList(listaPilotos);
    ll_deleteLinkedList(listaVuelosCortos);
    ll_deleteLinkedList(listaAlexLifeson);

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
    int r = 1;
    int tam = ll_len(pArrayListAvion);
    FILE* f;
    eAvion* auxAvion;

    f = fopen(path, "w");

    if(f == NULL)
    {
        printf("Error al abrir el archivo\n\n");
    }
    else
    {
        fprintf(f, "idVuelo,idAvion,idPiloto,fecha,destino,cantPasajeros,horaDespegue,horaLlegada\n");

        for(int i=0; i<tam; i++)
        {
            auxAvion = (eAvion*)ll_get(pArrayListAvion, i);
            fprintf(f, "%d,%d,%d,%d/%d/%d,%s,%d,%d,%d\n", auxAvion->idVuelo, auxAvion->idAvion, auxAvion->idPiloto, auxAvion->dia, auxAvion->mes, auxAvion->anio, auxAvion->destino, auxAvion->cantPasajeros, auxAvion->horaDespegue, auxAvion->horaLlegada);
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
    char buffer[10][1500];
    eAvion* auxAvion;

    cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^/]/%[^/]/%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8], buffer[9]);

    while(!feof(pFile))
    {
        cant = fscanf(pFile, "%[^,],%[^,],%[^,],%[^/]/%[^/]/%[^,],%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8], buffer[9]);
        if(cant == 10)
        {
            auxAvion = avion_newParametros(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8], buffer[9]);
            if(auxAvion != NULL)
            {
                ll_add(pArrayListAvion, auxAvion);
                r = 1;
            }
        }
    }

    if(r == 1)
    {
        printf("\nAviones cargados con exito!!\n\n");
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
        newAvion->dia = 0;
        newAvion->mes = 0;
        newAvion->anio = 0;
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
eAvion* avion_newParametros(char* idVueloStr,char* idAvionStr,char* idPilotoStr, char* diaStr, char* mesStr, char* anioStr, char* destinoStr,
                                char* cantPasajerosStr, char* horaDespegueStr, char* horaLlegadaStr)
{
    eAvion* newAvion;

    newAvion = avion_new();

    if(newAvion != NULL)
    {
        if(avion_setIdVuelo(newAvion, atoi(idVueloStr))
        || avion_setIdAvion(newAvion, atoi(idAvionStr))
        || avion_setIdPiloto(newAvion, atoi(idPilotoStr))
        || avion_setDia(newAvion, atoi(diaStr))
        || avion_setMes(newAvion, atoi(mesStr))
        || avion_setAnio(newAvion, atoi(anioStr))
        || avion_setDestino(newAvion, destinoStr)
        || avion_setCantPasajeros(newAvion, atoi(cantPasajerosStr))
        || avion_setHoraDespegue(newAvion, atoi(horaDespegueStr))
        || avion_setHoraLlegada(newAvion, atoi(horaLlegadaStr)))
        {
            free(newAvion);
            newAvion = NULL;
        }
    }

    return newAvion;
}



/** \brief Valida el idVuelo puesto como segundo parámetro y se lo asigna al avion
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setIdVuelo(eAvion* this,int idVuelo)
{
    int error = 1;

    if(this != NULL && idVuelo >= 0 && idVuelo <= 20000)
    {
        this->idVuelo = idVuelo;
        error = 0;
    }

    return error;
}



/** \brief Valida el idAvion puesto como segundo parámetro y se lo asigna al avion
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setIdAvion(eAvion* this,int idAvion)
{
    int error = 1;

    if(this != NULL && idAvion >= 0 && idAvion <= 20000)
    {
        this->idAvion = idAvion;
        error = 0;
    }

    return error;
}


/** \brief Valida el idPiloto puesto como segundo parámetro y se lo asigna al avion
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setIdPiloto(eAvion* this,int idPiloto)
{
    int error = 1;

    if(this != NULL && idPiloto >= 0 && idPiloto <= 20000)
    {
        this->idPiloto = idPiloto;
        error = 0;
    }

    return error;
}



/** \brief Valida el dia puesto como segundo parámetro y se lo asigna al avion
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setDia(eAvion* this, int dia)
{
    int error = 1;

    if(this != NULL && dia > 0 && dia <= 31)
    {
        this->dia = dia;
        error = 0;
    }

    return error;
}



/** \brief Valida el mes puesto como segundo parámetro y se lo asigna al avion
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setMes(eAvion* this, int mes)
{
    int error = 1;

    if(this != NULL && mes > 0 && mes <= 12)
    {
        this->mes = mes;
        error = 0;
    }

    return error;
}


/** \brief Valida el año puesto como segundo parámetro y se lo asigna al avion
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setAnio(eAvion* this, int anio)
{
    int error = 1;

    if(this != NULL && anio > 0 && anio <= 3000)
    {
        this->anio = anio;
        error = 0;
    }

    return error;
}


/** \brief Valida el destino puesto como segundo parámetro y se lo asigna al auto
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setDestino(eAvion* this,char* destino)
{
    int error = 1;

    if(this != NULL && strlen(destino) >= 3 && strlen(destino) < 20)
    {
        strcpy(this->destino, destino);
        error = 0;
    }

    return error;
}


/** \brief Valida la cantidad de pasajeros puestos como segundo parámetro y se lo asigna al auto
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setCantPasajeros(eAvion* this,int cantPasajeros)
{
    int error = 1;

    if(this != NULL && cantPasajeros >= 0 && cantPasajeros <= 20000)
    {
        this->cantPasajeros = cantPasajeros;
        error = 0;
    }

    return error;
}


/** \brief Valida la hora de despegue puesta como segundo parámetro y se lo asigna al auto
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setHoraDespegue(eAvion* this,int horaDespegue)
{
    int error = 1;

    if(this != NULL && horaDespegue >= 0 && horaDespegue <= 23)
    {
        this->horaDespegue = horaDespegue;
        error = 0;
    }

    return error;
}



/** \brief Valida la hora de llegada puesta como segundo parámetro y se lo asigna al auto
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int avion_setHoraLlegada(eAvion* this,int horaLlegada)
{
    int error = 1;

    if(this != NULL && horaLlegada >= 0 && horaLlegada <= 23)
    {
        this->horaLlegada = horaLlegada;
        error = 0;
    }

    return error;
}




/** \brief Muestra un avion
 *
 * \param int error = 1;
 * \param
 * \return error;
 *
 */
int mostrarAvion(eAvion* avion, LinkedList* listaPilotos)
{
    int error = 1;
    char nombreEncontrado[20];
    int tamPilotos;
    tamPilotos = ll_len(listaPilotos);
    ePiloto* auxPiloto;
    int todoOk = 0;

    for(int i=0; i<tamPilotos; i++)
    {
        auxPiloto = (ePiloto*)ll_get(listaPilotos, i);

        if(auxPiloto != NULL)
        {
            if(auxPiloto->id == avion->idPiloto)
            {
                strcpy(nombreEncontrado, auxPiloto->nombre);
                todoOk = 1;
            }
        }
    }

    if(avion != NULL && todoOk == 1)
    {
        printf("%d        %d        %s       %d/%d/%d     %13s        %d            %d               %d\n", avion->idVuelo, avion->idAvion, nombreEncontrado, avion->dia, avion->mes, avion->anio, avion->destino, avion->cantPasajeros, avion->horaDespegue, avion->horaLlegada);
        error = 0;
    }

    return error;
}



/** \brief Muestra los aviones de la lista.
 *
 * \param int r = -1;
 * \param int flag = 0;
 * \param int tam = ll_len(lista);
 * \param eAvion* auxAvion;
 * \return r;
 *
 */
int mostrarAviones(LinkedList* lista, LinkedList* listaPilotos)
{
    int r = -1;
    int flag = 0;

    int tam = ll_len(lista); //Contiene el tamaño de la lista
    eAvion* auxAvion;

    if(lista != NULL)
    {
        printf("IdVuelo  idAvion    Piloto            Fecha             Destino   Cant. pasajeros   Hora despegue   Hora llegada\n");
        printf("-------------------------------------------------------------------------------------------------------------\n");
        for(int i=0; i<tam; i++)
        {
            auxAvion = (eAvion*)ll_get(lista, i); //Mediante el indice obtiene la ubicacion del avion
            if(auxAvion != NULL)
            {
                mostrarAvion(auxAvion, listaPilotos);
                flag = 1;
            }
        }
        if(flag == 0)
        {
            printf("No hay vuelos para mostrar\n");
        }
        printf("\n\n");
        r = 1;
    }

    return r;
}


int menu()
{
    int opcion;

    printf("*** MENU DE OPCIONES ***\n\n");
    printf("1. Cargar archivo\n");
    printf("2. Imprimir vuelos\n");
    printf("3. Cantidad de pasajeros\n");
    printf("4. Cantidad de pasajeros a Irlanda\n");
    printf("5. Filtrar vuelos cortos\n");
    printf("6. Listar vuelos a Portugal\n");
    printf("7. Filtrar a Alex Lifeson\n");
    printf("8. Salir\n\n");

    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}


void cantidadTotalPasajeros(LinkedList* lista)
{
    int tam;
    int acumulador = 0;
    tam = ll_len(lista);
    eAvion* auxAvion;
    int todoOk = 0;


    if(lista != NULL)
    {
        for(int i=0; i<tam; i++)
        {
            auxAvion = (eAvion*)ll_get(lista, i);

            if(auxAvion != NULL)
            {
                acumulador += auxAvion->cantPasajeros;
                todoOk = 1;
            }
        }
    }


    if(todoOk == 1)
    {
        printf("La cantidad total de pasajeros es: %d\n\n", acumulador);
    }
    else
    {
        printf("Error, no se pudo calcular\n\n");
    }
}




void cantidadPasajerosIrlanda(LinkedList* lista)
{
    int tam;
    tam = ll_len(lista);
    eAvion* auxAvion;
    int acumulador = 0;
    int todoOk = 0;


    if(lista != NULL)
    {
        for(int i=0; i<tam; i++)
        {
            auxAvion = (eAvion*)ll_get(lista, i);

            if(auxAvion != NULL && strcmp(auxAvion->destino, "Irlanda") == 0)
            {
                acumulador += auxAvion->cantPasajeros;
                todoOk = 1;
            }
        }
    }

    if(todoOk == 1)
    {
        printf("La cantidad total de pasajeros que viajaron a Irlanda es: %d\n\n", acumulador);
    }
    else
    {
        printf("Error, no se pudo calcular\n\n");
    }
}


void vuelosAPortugal(LinkedList* lista, LinkedList* listaPilotos)
{
    int tam;
    tam = ll_len(lista);
    eAvion* auxAvion;
    int todoOk = 0;

    printf("\nIdVuelo  idAvion    Piloto            Fecha             Destino   Cant. pasajeros   Hora despegue   Hora llegada\n");
    printf("-------------------------------------------------------------------------------------------------------------\n");

    if(lista != NULL)
    {
        for(int i=0; i<tam; i++)
        {
            auxAvion = (eAvion*)ll_get(lista, i);

            if(auxAvion != NULL && strcmp(auxAvion->destino, "Portugal") == 0)
            {
                mostrarAvion(auxAvion, listaPilotos);
                todoOk = 1;
            }
        }
    }

    if(todoOk == 1)
    {
        printf("Listados con exito!\n\n");
    }
    else
    {
        printf("Error al listar\n\n");
    }
}



int filtrarxVuelosCortos(void* unAvion)
{
    int auxReturn = 0;
    eAvion* x;

    if(unAvion != NULL)
    {
        x = (eAvion*)unAvion;

        if((x->horaDespegue + 1) == x->horaLlegada || (x->horaDespegue + 2) == x->horaLlegada || (x->horaDespegue + 3) == x->horaLlegada)
        {
            auxReturn = 1;
        }
    }

    return auxReturn;
}



int filtrarSinAlexLifeson(void* unAvion)
{
    int auxReturn = 0;
    eAvion* x;

    if(unAvion != NULL)
    {
        x = (eAvion*)unAvion;

        if(x->idPiloto != 1)
        {
            auxReturn = 1;
        }
    }

    return auxReturn;
}
