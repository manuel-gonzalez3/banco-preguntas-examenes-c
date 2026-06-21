// Este archivo se utiliza para compartir datos y funciones comunes entre los archivos listarPreguntas.c, modificarPregunta.c y agregarPregunta.c

#ifndef DATOSCOMUNES_H
#define DATOSCOMUNES_H

#include "definiciones.h"

void listarPreguntas(); // Función definida en listarPreguntas.c, lista todas las preguntas del archivo y crea un arreglo de preguntas

void imprimirPregunta(struct Pregunta *nueva); // Función definida en agregarPregunta.c, imprime una estructura de pregunta individual

void guardarPregunta(struct Pregunta *nueva, FILE *archivo); // Función definida en agregarPregunta.c, guarda una estructura de pregunta en el archivo

void crearArregloPreguntas(FILE *archivo); // Función definida en listarPreguntas.c, crea un arreglo de preguntas a partir del archivo

void copiarString(char *destino, FILE *archivo, char separador); // Función definida en listarPreguntas.c, copia cadenas de caracteres hasta encontrar un punto y coma

extern int cantPreguntas; // Variable global para contar el número de preguntas, asignada en listarPreguntas.c. Utilizada en modificarPregunta.c y listarPreguntas.c

extern int cantExamenes; // Variable global para contar el número de exámenes, asignada en listarExamenes.c. Utilizada en listarPreguntas.c

extern int cantPreguntasExamen; // Variable global para contar el número de preguntas en el examen, asignada en menuExamen.c. Utilizada en menuExamen.c y crearExamen.c

extern int cantCapitulos; // Variable global para contar el número de capítulos, asignada en menuExamen.c. Utilizada en menuExamen.c y crearExamen.c

extern int flagArchivoPregVacio; // Variable global para verificar si el archivo de preguntas está vacío, asignada en listarPreguntas.c. Utilizada en modificarPregunta.c y listarPreguntas.c

extern int flagArchivoExamVacio; // Variable global para verificar si el archivo de exámenes está vacío, asignada en listarExamenes.c. Utilizada en menuExamen.c y listarExamenes.c

struct Pregunta preguntas[N]; // Arreglo de preguntas, asignado en listarPreguntas.c. Utilizado en modificarPregunta.c y listarPreguntas.c

struct Capitulo capitulos[N]; // Arreglo de capítulos, asignado en menuExamen.c. Utilizado en menuExamen.c

struct Examen examenes[N]; // Arreglo de exámenes, asignado en listarExamenes.c. Utilizado en listarExamenes.c

#endif
