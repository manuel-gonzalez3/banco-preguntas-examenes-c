#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "agregarPregunta.c"
#include "listarPreguntas.c"
#include "modificarPregunta.c"
#include "eliminarPregunta.c"
void menuBanco()
{
    int opcion;
    do
    {
        system("cls");
        printf("1. Agregar pregunta\n");
        printf("2. Modificar pregunta\n");
        printf("3. Eliminar pregunta\n");
        printf("4. Listar preguntas\n");
        printf("0. Volver\n");
        while (1)
        {
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            fflush(stdin);
            if(opcion >= 0 && opcion <= 4)
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
                nuevaPregunta();
                break;
            case 2:
                menuModificarPregunta();
                break;
            case 3:
                menuEliminarPregunta();
                break;
            case 4:
                menuListar();
                break;
            case 0:
                break;
        }
    }while (opcion != 0);
}

