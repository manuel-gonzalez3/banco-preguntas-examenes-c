#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "menuBanco.c"
#include "menuExamen.c"
#include "menuCorreccion.c"
void main()
{
    int opcion;
    do
    {
        system("cls");
        printf("1. Administrar banco de preguntas\n");
        printf("2. Agregar Examen\n");
        printf("3. Corregir examen\n");
        printf("0. Salir\n");
        while (1)
        {
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            fflush(stdin);
            if(opcion >= 0 && opcion <= 3)
            {
                break;
            }
            else
            {
                printf("Opcion invalida\n");
            }
        }
        switch(opcion)
        {
            case 1:
                menuBanco();
                break;
            case 2:
                menuExamen();
                break;
            case 3:
                menuCorreccion();
                break;
            case 0:
                printf("PROGRAMA FINALIZADO\n");
                break;
        }
    } while (opcion != 0);
}