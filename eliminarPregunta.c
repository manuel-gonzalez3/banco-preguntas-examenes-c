#include "definiciones.h"
#include "datosComunes.h"
//declaracion de funciones
void menuEliminarPregunta();

/**
 * @brief Muestra un menú para eliminar una pregunta.
 * 
 * Esta función muestra un menú al usuario, enumerando todas las preguntas de un archivo.
 * El usuario puede elegir una pregunta para eliminar ingresando el número correspondiente.
 * La función valida la entrada y elimina la pregunta seleccionada del arreglo.
 * 
 * @param Ninguno
 * @return Ninguno
 */
void eliminarPregunta(int nPregunta);

//implementacion de funciones
void menuEliminarPregunta()
{
    int nPregunta = 0;
    do
    {
        listarPreguntas(); // se listan las preguntas del archivo, esta función genera el arreglo de preguntas que se usa en este archivo
        if(flagArchivoPregVacio == 0)
        {
            while(1)
            {
                printf("Ingrese el número de la pregunta que desea eliminar (0-Volver): ");
                scanf("%i", &nPregunta);
                fflush(stdin);
                if(nPregunta >= 0 && nPregunta <= cantPreguntas)
                {
                    break;
                }
                else
                {
                    printf("Número inválido\n");
                }
            }
            if(nPregunta != 0)
            {
                eliminarPregunta(nPregunta); //se elimina la pregunta del arreglo
            }
        }
        else
        {
            break;
        }
    } while(nPregunta != 0);
}

void eliminarPregunta(int nPregunta)
{
    char numPregunta[T]; // Variable temporal para almacenar el número de la pregunta
    for(int i = nPregunta-1; i < cantPreguntas-1; i++) // Recorre el arreglo de preguntas desde la pregunta seleccionada hasta la penúltima pregunta
    {
        strcpy(numPregunta, preguntas[i].numero); // Copia el número de la pregunta en la variable temporal
        preguntas[i] = preguntas[i+1]; // Desplaza el arreglo de preguntas para eliminar la pregunta seleccionada
        strcpy(preguntas[i].numero, numPregunta); // Copia el número de la pregunta de vuelta a la pregunta desplazada

    }
    cantPreguntas--; // Disminuye el número total de preguntas
    actualizarArchivo(); // Actualiza el archivo con las preguntas modificadas
    printf("PREGUNTA ELIMINADA\n"); // Imprime un mensaje indicando que la pregunta ha sido eliminada
    system("pause"); // Pausa la ejecución del programa
}
