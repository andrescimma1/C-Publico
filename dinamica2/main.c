#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 10

typedef struct
{
    int id;
    char nombre[20];
    char sexo;
    float altura;
}ePersona;

int personaSetId(ePersona* persona, int id);
int personaSetNombre(ePersona* persona, char* nombre);
int personaSetSexo(ePersona* persona, char sexo);
int personaSetAltura(ePersona* persona, float altura);

int personaGetId(int* pId, ePersona* persona);
int personaGetNombre(char* pNombre, ePersona* persona);
int personaGetSexo(char* pSexo, ePersona* persona);
int personaGetAltura(float* pAltura, ePersona* persona);

int initPersonas(ePersona** vec, int tam);
int buscarLibrePersonas(int* pIndice, ePersona** vec, int tam);
int mostrarPersona(ePersona* persona);
int mostrarPersonas(ePersona** vec, int tam);

ePersona* new_Persona();
ePersona* new_PersonaParam(int id, char* nombre, char sexo, float altura);

int destruirPersona(ePersona* persona);
int buscarPersona(int* pIndice, int id, ePersona** vec, int tam);

int main()
{
    int indiceLibre;
    int indiceBaja;
    ePersona** lista = (ePersona**)malloc(TAM * sizeof(ePersona*));
    ePersona* auxPersona;

    if(lista == NULL)
    {
        printf("No se pudo conseguir memoria\n");
        exit(EXIT_FAILURE);
    }

    if(!initPersonas(lista, TAM))
    {
        printf("Personas inicializadas con exito!\n");
    }
    else
    {
        printf("No se inicializaron personas\n");
    }

    if(buscarLibrePersonas(&indiceLibre, lista, TAM))
    {
        printf("Alguno de los punteros es NULL\n");
    }

    if(indiceLibre == -1)
    {
        printf("No hay mas lugar\n");
    }
    else
    {
        printf("%d\n", indiceLibre);

        auxPersona = new_PersonaParam(12000, "Jose", 'm', 1.82);

        //mostrarPersona(auxPersona);

        if(auxPersona == NULL)
        {
            printf("No se pudo conseguir memoria o datos invalidos\n");
        }
        else
        {
            *(lista + indiceLibre) = auxPersona;

            printf("Alta exitosa!\n");
        }
    }

    printf("\n--------------------------------------\n");
    mostrarPersonas(lista, TAM);
    printf("\n--------------------------------------\n");

    if(buscarLibrePersonas(&indiceLibre, lista, TAM))
    {
        printf("Alguno de los punteros es NULL\n");
    }

    if(indiceLibre == -1)
    {
        printf("No hay mas lugar\n");
    }
    else
    {
        printf("%d\n", indiceLibre);

        auxPersona = new_PersonaParam(12040, "Carlos", 'm', 1.76);

       // mostrarPersona(auxPersona);

        if(auxPersona == NULL)
        {
            printf("No se pudo conseguir memoria o datos invalidos\n");
        }
        else
        {
            *(lista + indiceLibre) = auxPersona;

            printf("Alta exitosa!\n");
        }
    }

    mostrarPersonas(lista, TAM);
    printf("\n--------------------------------------\n");

    if(buscarLibrePersonas(&indiceLibre, lista, TAM))
    {
        printf("Alguno de los punteros es NULL\n");
    }

    if(indiceLibre == -1)
    {
        printf("No hay mas lugar\n");
    }
    else
    {
        printf("%d\n", indiceLibre);

        auxPersona = new_PersonaParam(13014, "Juana", 'f', 1.65);

       // mostrarPersona(auxPersona);

        if(auxPersona == NULL)
        {
            printf("No se pudo conseguir memoria o datos invalidos\n");
        }
        else
        {
            *(lista + indiceLibre) = auxPersona;

            printf("Alta exitosa!\n");
        }
    }

    mostrarPersonas(lista, TAM);
    printf("\n--------------------------------------\n");

    buscarPersona(&indiceBaja, 12040, lista, TAM);

    if(indiceBaja == -1)
    {
        printf("No hay ninguna persona con esa id\n");
    }
    else
    {
        destruirPersona(*(lista + indiceBaja));
        *(lista + indiceBaja) = NULL;
    }

    mostrarPersonas(lista, TAM);
    printf("\n-------------------------------------\n");

    return 0;
}

int initPersonas(ePersona** vec, int tam)
{
    int error = 1;

    if(vec != NULL)
    {
        for(int i=0; i<tam; i++)
        {
            *(vec + i) = NULL;
        }

        error = 0;
    }

    return error;
}

int buscarLibrePersonas(int* pIndice, ePersona** vec, int tam)
{
    int error = 1;

    if(vec != NULL && pIndice != NULL)
    {
        *pIndice = -1;

        for(int i=0; i<tam; i++)
        {
            if(*(vec + i) == NULL)
            {
               *pIndice = i;
                break;
            }
        }

        error = 0;
    }

    return error;
}

int mostrarPersona(ePersona* persona)
{
    int error = 1;

    if(persona != NULL)
    {
        printf("%d  %10s     %c          %.2f\n", persona->id, persona->nombre, persona->sexo, persona->altura);
        error = 0;
    }

    return error;
}

int mostrarPersonas(ePersona** vec, int tam)
{
    int error = 1;
    int flag = 0;

    if(vec != NULL)
    {
        printf("ID         NOMBRE    SEXO     ALTURA\n");
        for(int i=0; i<tam; i++)
        {
            if(*(vec + i) != NULL)
            {
                mostrarPersona(*(vec + i));
                flag = 1;
            }
        }
        if(flag == 0)
        {
            printf("No hay personas para mostrar\n");
        }
        error = 0;
    }

    return error;
}

ePersona* new_Persona()
{
    ePersona* nuevaPersona;
    nuevaPersona = (ePersona*)malloc(sizeof(ePersona));

    if(nuevaPersona != NULL)
    {
        nuevaPersona->id = 0;
        strcpy(nuevaPersona->nombre, "");
        nuevaPersona->sexo = ' ';
        nuevaPersona->altura = 0;
    }

    return nuevaPersona;
}

ePersona* new_PersonaParam(int id, char* nombre, char sexo, float altura)
{
    ePersona* nuevaPersona;

    nuevaPersona = new_Persona();

    if(nuevaPersona != NULL)
    {
        if(personaSetId(nuevaPersona, id)
        || personaSetNombre(nuevaPersona, nombre)
        || personaSetSexo(nuevaPersona, sexo)
        || personaSetAltura(nuevaPersona, altura))
        {
            free(nuevaPersona);
            nuevaPersona = NULL;
        }
    }

    return nuevaPersona;
}


int personaSetId(ePersona* persona, int id)
{
    int error = 1;

    if(persona != NULL && id >= 10000 && id <= 20000)
    {
        persona->id = id;
        error = 0;
    }

    return error;
}

int personaSetNombre(ePersona* persona, char* nombre)
{
    int error = 1;

    if(persona != NULL && strlen(nombre) >= 3 && strlen(nombre) < 20)
    {
        strcpy(persona->nombre, nombre);
        error = 0;
    }

    return error;
}

int personaSetSexo(ePersona* persona, char sexo)
{
    int error = 1;

    if(persona != NULL)
    {
        if(sexo == 'f' || sexo == 'm')
        {
            persona->sexo = sexo;
            error = 0;
        }
    }

    return error;
}

int personaSetAltura(ePersona* persona, float altura)
{
    int error = 1;

    if(persona != NULL && altura >= 0 && altura < 4)
    {
        persona->altura = altura;
        error = 0;
    }

    return error;
}

int personaGetId(int* pId, ePersona* persona)
{
    int error = 1;

    if(persona != NULL && pId != NULL)
    {
        *pId = persona->id;
        error = 0;
    }

    return error;
}


int personaGetNombre(char* pNombre, ePersona* persona)
{
    int error = 1;

    if(persona != NULL && pNombre != NULL)
    {
        strcpy(pNombre, persona->nombre);
        error = 0;
    }

    return error;
}


int personaGetSexo(char* pSexo, ePersona* persona)
{
    int error = 1;

    if(persona != NULL && pSexo != NULL)
    {
        *pSexo = persona->sexo;
        error = 0;
    }

    return error;
}

int personaGetAltura(float* pAltura, ePersona* persona)
{
    int error = 1;

    if(persona != NULL && pAltura != NULL)
    {
        *pAltura = persona->altura;
        error = 0;
    }

    return error;
}


int destruirPersona(ePersona* persona)
{
    int error = 1;

    if(persona != NULL)
    {
        free(persona);
        error = 0;
    }

    return error;
}


int buscarPersona(int* pIndice, int id, ePersona** vec, int tam)
{
    int error = 1;

    if(vec != NULL && pIndice != NULL)
    {
        *pIndice = -1;

        for(int i=0; i<tam; i++)
        {
            if(*(vec + i) != NULL && (*(vec + i))->id == id)
            {
               *pIndice = i;
                break;
            }
        }

        error = 0;
    }

    return error;
}
