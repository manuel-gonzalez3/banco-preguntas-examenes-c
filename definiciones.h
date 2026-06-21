//archivo base, con todas las bibliotecas, variables globales y estructuras comunes
#ifndef DEFINICIONES_H //para poder usarlo en cualquier archivo 
#define DEFINICIONES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define C 4
#define T 30
#define X 500
#define N 1000

struct Pregunta
{
    char numero[T];
    char numeroCapitulo[T];
    char nombreCapitulo[X];
    char numeroSubcapitulo[T];
    char nombreSubcapitulo[X];
    char pregunta[N];
    char opciones[C][T];
    char respuesta;
};

struct Subcapitulo {
    char numSubcapitulo[T];
    char nombreSubcapitulo[X];
    int cantPreguntas;
    int seleccionado;
};

struct Capitulo {
    char numCapitulo[T];
    char nombreCapitulo[X];
    int cantSubcapitulos;
    int cantPreguntas;
    int seleccionado;
    int agregado;
    struct Subcapitulo subcapitulos[N];
};
struct Examen
{
    char numero[T];
    char fecha[11];
    char cantPreguntas[T];
    char capitulosSubcapitulos[X];
    char preguntas[X];
};
#endif