#include <stdio.h>
#include <stdlib.h>

void saludar(void);
void despedir(void);
void brindar(void);

void queHago(void (*callback)(void));

int main()
{
    queHago(saludar);
    queHago(brindar);
    queHago(despedir);
    return 0;
}

void saludar(void)
{
    printf("Hola\n");
}

void despedir(void)
{
    printf("Chau\n");
}

void brindar(void)
{
    printf("Chin chin\n");
}

void queHago(void (*callback)(void))
{
    callback();
}
