#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "definiciones.h"
#include "datosComunes.h"
int cantPreguntas = 0; //variable global definida en definiciones.h, se tiene que inicializar aqui para que no haya error de compilacion
int flagArchivoPregVacio = 0; //variable global definida en definiciones.h, se tiene que inicializar aqui para que no haya error de compilacion
/**
 * @brief Muestra el menú de opciones para listar preguntas.
 */
void menuListar();

/**
 * @brief Copia una cadena de caracteres desde un archivo hasta encontrar un separador.
 * 
 * @param destino Puntero al arreglo donde se copiará la cadena.
 * @param archivo Puntero al archivo del cual se leerá la cadena.
 * @param separador Caracter separador que indica el fin de la cadena.
 */
void copiarString(char *destino, FILE *archivo, char separador);

/**
 * @brief Imprime todas las preguntas almacenadas en un archivo.
 */
void imprimirPreguntas();

/**
 * @brief Filtra las preguntas almacenadas en un archivo según ciertos criterios.
 */
void filtrarPreguntas();

/**
 * @brief Verifica si una cadena de caracteres representa un número válido.
 * 
 * @param num Puntero a la cadena de caracteres a verificar.
 * @param flagCapitulo Bandera que indica si se está verificando un número de capítulo.
 * @return 1 si la cadena es un número válido, 0 en caso contrario.
 */
int verificarNumero(char *num, int flagCapitulo);

//implementacion de funciones
void menuListar()
{
    int opcion;
    do
    {  
        listarPreguntas();
        printf("1. Filtrar\n");
        printf("0. Volver\n");
        while (1)
        {
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            fflush(stdin);
            if(opcion >= 0 && opcion <= 1)
            {
                break;
            }
            else
            {
                printf("Opcion invalida\n");
            }
        }
        if(opcion != 0)
        {
            filtrarPreguntas();
        }
    } while (opcion != 0);
    
}

//MOSTRAR TODAS LAS PREGUNTAS
void listarPreguntas()
{
    system("cls");
    printf("PREGUNTAS GUARDADAS:\n");
    FILE *archivo;
    archivo = fopen("preguntas.txt", "rb");
    if (archivo == NULL || fgetc(archivo) == EOF) //si el archivo no existe o esta vacio
    {
        printf("No hay preguntas guardadas.\n");
        flagArchivoPregVacio = 1; //asigna 1 a la variable global flagArchivoPregVacio, variable global definida en definiciones.h
    }
    else
    {
        crearArregloPreguntas(archivo);
        imprimirPreguntas();
    }
    fclose(archivo);
}
//fc para crear el arreglo y fc auxiliar para copiar strings

void crearArregloPreguntas(FILE *archivo)
{
    char ch;
    int cont = 0;
    char numero[T], numCap[T], nomCap[X], numSub[T], nomSub[X], preg[N], opc[C][T], resp; //variables auxiliares para guardar los datos de la pregunta
    fseek(archivo, 0, SEEK_SET);
    while (ch != EOF)
    {
        //leer los datos de la linea, separados por punto y coma, y guardarlos en cada variable
        copiarString(numero, archivo, ';'); 
        copiarString(numCap, archivo, ';');
        copiarString(nomCap, archivo, ';');
        copiarString(numSub, archivo, ';');
        copiarString(nomSub, archivo, ';');
        copiarString(preg, archivo, ';');
        for(int i = 0; i < C; i++) //copiar las opciones
        {
            copiarString(opc[i], archivo, ';'); 
        }
        //la respuesta no termina con coma, por lo que copiar string no funciona. Ademas resp es un unico caractere: se lee el caracter directamente
        ch = fgetc(archivo);
        resp = ch; //almacena el caracter leido en respuesta

        //guardar los datos en la estructura
        strcpy(preguntas[cont].numero, numero);
        strcpy(preguntas[cont].numeroCapitulo, numCap);
        strcpy(preguntas[cont].nombreCapitulo, nomCap);
        strcpy(preguntas[cont].numeroSubcapitulo, numSub);
        strcpy(preguntas[cont].nombreSubcapitulo, nomSub);
        strcpy(preguntas[cont].pregunta, preg);
        for(int i = 0; i < C; i++)
        {
            strcpy(preguntas[cont].opciones[i], opc[i]);
        }
        preguntas[cont].respuesta = resp;

        ch = fgetc(archivo); //avanza al salto de linea
        cont++;
        ch = fgetc(archivo); //avanza al eof o al siguiente numero de pregunta
        if(ch != EOF)
        {
            fseek(archivo, -1, SEEK_CUR); //si no es eof, es un numero de pregunta: retrocede un caracter para que copiarString(numero, archivo) pueda leerlo correctamente (si no arranca desde el segundo caracter de la linea)
        }
    }
    cantPreguntas = cont; //asigna la cantidad de preguntas, variable global definida en definiciones.h
}
void copiarString(char *destino, FILE *archivo, char separador) //copia strings hasta encontrar un punto y coma
{
    int i = 0;
    char ch = fgetc(archivo); //arranca en el primer caracter o en el caracterer dsp del punto y coma
    while (ch != separador) //recorre la linea hasta encontrar el punto y coma o el salto de linea
    {
        if (i < X-1) //asegura que no se exceda el tamaño del buffer
        {
            destino[i] = ch; //almacena el caracter leido en el buffer
            i++;
        }
        ch = fgetc(archivo); //avanza al siguiente caracter
    }
    destino[i] = '\0';  // Agrega el carácter nulo al final del buffer
}
void imprimirPreguntas()
{
    for(int i = 0; i< cantPreguntas; i++)
    {
        imprimirPregunta(&preguntas[i]); //funcion de agregarPregunta.c, imprime cada estructura de pregunta
    }
}

//FILTRA LAS PREGUNTAS POR CAPITULO Y SUBCAPITULO
void filtrarPreguntas()
{
    char numCap[T], numSub[T];
    int i;
    while(1)
    {
        printf("Ingrese el numero del capitulo('*' Volver): ");
        scanf("%s", &numCap);
        fflush(stdin);
        if (verificarNumero(numCap, 0) == 1 || strcmp(numCap, "*") == 0) //chequear que el num de capitulo esta en el arreglo de preguntas
        {
            break;
        }
        else
        {
            printf("Numero de capitulo invalido\n");
        }
    }
    if(strcmp(numCap, "*") != 0) //si no se ingreso * para volver
    {
        int cont = 0;
        for(int i = 0; i < cantPreguntas; i++) //itera por el arreglo con las preguntas de ese capitulo
        {
                if(strcmp(preguntas[i].numeroCapitulo, numCap) == 0) //si encuentra una pregunta con el numero de capitulo ingresado, la guarda en el arreglo de preguntas y aumenta el contador
                {
                    preguntas[cont] = preguntas[i]; 
                    cont++;
                }
        }
        cantPreguntas = cont; //actualiza la cantidad de preguntas para poder imprimir
        system("cls");
        printf("PREGUNTAS DEL CAPITULO %s:\n", numCap);
        imprimirPreguntas(); //imprime las preguntas de ese capitulo
        while(1)
        {
            printf("Ingrese el numero del subcapitulo('*' Volver): ");
            scanf("%s", &numSub);
            fflush(stdin);
            if (verificarNumero(numSub, 1) == 1 || strcmp(numSub, "*") == 0) //chequear que el num de subcapitulo esta en el arreglo de preguntas
            {
                break;
            }
            else
            {
                printf("Numero de subcapitulo invalido\n");
            }
        }
        if(strcmp(numSub, "*") != 0) //si no se ingreso * para volver
        {
            cont = 0;
            for(int i = 0; i < cantPreguntas; i++)//itera por el arreglo con las preguntas de ese capitulo
            {
                    if(strcmp(preguntas[i].numeroSubcapitulo, numSub) == 0) //si encuentra una pregunta con el numero de capitulo ingresado, la guarda en el arreglo de preguntas y aumenta el contador
                    {
                        preguntas[cont] = preguntas[i]; 
                        cont++;
                    }
            }
            cantPreguntas = cont; //actualiza la cantidad de preguntas para poder imprimir
            system("cls");
            printf("PREGUNTAS DEL CAPITULO %s, SUBCAPITULO %s:\n", numCap, numSub);
            imprimirPreguntas(); //imprime las preguntas de ese capitulo y subcapitulo
            system("pause");
        }
    }
}

int verificarNumero(char *num, int flagCapitulo)
{
    for(int i =0; i<cantPreguntas; i++) //itera por el arreglo de preguntas
    {
        if(flagCapitulo == 0)
        {
            if(strcmp(preguntas[i].numeroCapitulo, num) == 0) //si encuentra el numero de capitulo, retorna 1
            {
                return 1;
            }
        }
        else
        {
            if(strcmp(preguntas[i].numeroSubcapitulo, num) == 0) //si encuentra el numero de subcapitulo, retorna 1
            {
                return 1;
            }
        }
    }
    return 0;
}
