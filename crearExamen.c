#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "definiciones.h"
#include "datosComunes.h"
/**
 * Crea un examen a partir de los capítulos seleccionados y escribe el examen en un archivo.
 * 
 * @param capitulos Arreglo de estructuras Capitulo que contiene los capítulos y subcapítulos seleccionados.
 */
void crearExamen(struct Capitulo capitulos[N]);

/**
 * Genera las preguntas del examen seleccionando aleatoriamente de las posibles preguntas.
 * 
 * @param posiblesPreguntasExamen Arreglo de enteros que contiene las posibles preguntas del examen.
 * @param preguntasExamen Arreglo de enteros donde se almacenarán las preguntas seleccionadas para el examen.
 * @param cantidadPreguntasSeleccionadas Cantidad de preguntas seleccionadas para el examen.
 */
void generarPreguntasExamen(int posiblesPreguntasExamen[], int preguntasExamen[], int cantidadPreguntasSeleccionadas);

/**
 * Escribe el examen en un archivo.
 * 
 * @param preguntasExamen Arreglo de enteros que contiene las preguntas del examen.
 * @param capitulos Arreglo de estructuras Capitulo que contiene los capítulos y subcapítulos seleccionados.
 */
void escribirExamenEnArchivo(int preguntasExamen[], struct Capitulo capitulos[N]);

/**
 * Obtiene la fecha actual en formato "dd-mm-yyyy".
 * 
 * @param fechaStr Cadena de caracteres donde se almacenará la fecha actual.
 * @param longitud Longitud de la cadena de caracteres.
 */
void obtenerFechaActual(char* fechaStr, int longitud);

/**
 * Obtiene el número del último examen generado y genera el número del próximo examen.
 * 
 * @param archivo Puntero al archivo donde se almacenan los exámenes.
 * @param numero Cadena de caracteres donde se almacenará el número del próximo examen.
 */
void obtenerNumeroExamen(FILE *archivo, char *numero);

//implementacion de funciones

void crearExamen(struct Capitulo capitulos[N])
{
    int posiblesPreguntasExamen[cantPreguntas];
    int preguntasExamen[cantPreguntasExamen];
    int cantidadPreguntasSeleccionadas = 0;

    // Iterar sobre los capítulos y subcapítulos para seleccionar las posibles preguntas del examen
    for (int i = 0; i < cantCapitulos; i++)
    {
        if (capitulos[i].seleccionado == 1)
        {
            for (int j = 0; j < capitulos[i].cantSubcapitulos; j++)
            {
                if (capitulos[i].subcapitulos[j].seleccionado == 1)
                {
                    for (int k = 0; k < cantPreguntas; k++) // Iterar sobre las preguntas
                    {
                        // Verificar si la pregunta pertenece al capítulo y subcapítulo seleccionados
                        if (strcmp(preguntas[k].numeroCapitulo, capitulos[i].numCapitulo) == 0 &&
                            strcmp(preguntas[k].numeroSubcapitulo, capitulos[i].subcapitulos[j].numSubcapitulo) == 0)
                        {
                            posiblesPreguntasExamen[cantidadPreguntasSeleccionadas++] = atoi(preguntas[k].numero);
                        }
                    }
                }
            }
        }
    }

    // Generar las preguntas del examen
    generarPreguntasExamen(posiblesPreguntasExamen, preguntasExamen, cantidadPreguntasSeleccionadas);

    // Escribir el examen en un archivo
    escribirExamenEnArchivo(preguntasExamen, capitulos);
}

void generarPreguntasExamen(int posiblesPreguntasExamen[], int preguntasExamen[], int cantidadPreguntasSeleccionadas) 
{
    srand(time(NULL));
    int seleccionadas[cantidadPreguntasSeleccionadas]; // Arreglo para marcar las preguntas seleccionadas
    memset(seleccionadas, 0, sizeof(seleccionadas)); // Inicializar el arreglo de selección en 0

    // Seleccionar preguntas aleatorias del arreglo de posibles preguntas
    for (int i = 0; i < cantPreguntasExamen; i++)
    {
        int preguntaSeleccionada;
        do
        {
            preguntaSeleccionada = rand() % cantidadPreguntasSeleccionadas;
        } while (seleccionadas[preguntaSeleccionada] == 1); // Repetir si la pregunta ya está seleccionada

        seleccionadas[preguntaSeleccionada] = 1; // Marcar como seleccionada
        preguntasExamen[i] = posiblesPreguntasExamen[preguntaSeleccionada]; // Asignar la pregunta al examen
    }
}

void escribirExamenEnArchivo(int preguntasExamen[], struct Capitulo capitulos[N])
{
    FILE *archivo = fopen("examenes.txt", "ab+");
    char numeroExamen[T];
    obtenerNumeroExamen(archivo, numeroExamen);

    // Obtener la fecha actual
    char fechaActual[11];
    obtenerFechaActual(fechaActual, sizeof(fechaActual));

    // Recopilar los capítulos y subcapítulos involucrados
    char capitulosSubcapitulos[X] = "";
    for (int i = 0; i < cantCapitulos; i++)
    {
        if (capitulos[i].seleccionado == 1)
        {
            strcat(capitulosSubcapitulos, capitulos[i].numCapitulo);
            strcat(capitulosSubcapitulos, ":");
            for (int j = 0; j < capitulos[i].cantSubcapitulos; j++)
            {
                if (capitulos[i].subcapitulos[j].seleccionado == 1)
                {
                    strcat(capitulosSubcapitulos, capitulos[i].subcapitulos[j].numSubcapitulo);
                    strcat(capitulosSubcapitulos, ",");
                }
            }
            // Remover la última coma si existe
            if (capitulosSubcapitulos[strlen(capitulosSubcapitulos) - 1] == ',')
            {
                capitulosSubcapitulos[strlen(capitulosSubcapitulos) - 1] = '\0';
            }
            strcat(capitulosSubcapitulos, "-");
        }
    }

    // Remover el último guion si existe
    if (capitulosSubcapitulos[strlen(capitulosSubcapitulos) - 1] == '-')
    {
        capitulosSubcapitulos[strlen(capitulosSubcapitulos) - 1] = '\0';
    }
    // Escribir los detalles del examen en el archivo
    fprintf(archivo, "%s;%s;%d;%s;", numeroExamen, fechaActual, cantPreguntasExamen, capitulosSubcapitulos);
    for (int i = 0; i < cantPreguntasExamen; i++)
    {
        fprintf(archivo, "%i", preguntasExamen[i]);
        if (i < cantPreguntasExamen - 1)
        {
            fprintf(archivo, ",");
        }
    }
    fprintf(archivo, "\n");
    fclose(archivo);
    printf("Examen generado exitosamente y guardado en 'examenes.txt'.\n");
}

void obtenerFechaActual(char* fechaStr, int longitud)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(fechaStr, longitud, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void obtenerNumeroExamen(FILE *archivo, char *numero) 
{
    char ch;
    long pos;
    int i = 0;
    fseek(archivo, 0, SEEK_END);  // se posiciona en el final del archivo
    if (ftell(archivo) == 0) 
    { // si vale 0 es porque el archivo está vacío (asigna 1)
        strcpy(numero, "1");
    } 
    else 
    {
        fseek(archivo, -2, SEEK_END); // retrocede dos caracteres para evitar el salto de línea al final del archivo
        pos = ftell(archivo);
        while (pos > 0) { // recorre el archivo hacia atrás hasta encontrar el comienzo de la última línea
            fseek(archivo, --pos, SEEK_SET);
            ch = fgetc(archivo);
            if (ch == '\n') {
                break;
            }
        }
        // si no está en el comienzo del archivo, se posiciona en el siguiente carácter
        if (pos > 0) {
            fseek(archivo, ++pos, SEEK_SET);
        } else {
            fseek(archivo, 0, SEEK_SET); // si está en el comienzo del archivo, se posiciona en el comienzo
        }
        ch = fgetc(archivo);
        while (ch != ';') { // recorre la línea hasta encontrar la coma
            if (i < T-1) { // asegura que no se exceda el tamaño del buffer
                numero[i] = ch; // almacena el carácter leído en número
                i++;
            }
            ch = fgetc(archivo); // leer el siguiente carácter
        }
        numero[i] = '\0';  // Agrega el carácter nulo al final del buffer
        int num = atoi(numero); // convertir el número de la última pregunta a entero, para incrementarlo
        sprintf(numero, "%i", num+1); // convertir el número de la nueva pregunta a string
        fseek(archivo, 0, SEEK_END); // se posiciona al final del archivo
    }
}