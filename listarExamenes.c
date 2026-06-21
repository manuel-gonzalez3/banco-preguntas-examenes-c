#include "definiciones.h"
#include "datosComunes.h"
int cantExamenes = 0; //variable global definida en definiciones.h, se tiene que inicializar aqui para que no haya error de compilacion
int flagArchivoExamVacio = 0; //variable global definida en definiciones.h, se tiene que inicializar aqui para que no haya error de compilacion
/**
 * Función: listarExamenes
 * Descripción: Esta función se encarga de listar los exámenes disponibles.
 * Parámetros: Ninguno.
 * Retorno: Ninguno.
 */
void listarExamenes();

/**
 * Función: crearArregloExamenes
 * Descripción: Esta función se encarga de crear un arreglo de exámenes a partir de un archivo.
 * Parámetros:
 *     - archivo: Puntero al archivo que contiene la información de los exámenes.
 * Retorno: Ninguno.
 */
void crearArregloExamenes(FILE *archivo);

/**
 * Función: imprimirExamenes
 * Descripción: Esta función se encarga de imprimir los exámenes disponibles.
 * Parámetros: Ninguno.
 * Retorno: Ninguno.
 */
void imprimirExamenes();

/**
 * Función: imprimirCapitulos
 * Descripción: Esta función se encarga de imprimir los capítulos de un examen específico. Separando el stiring CapitulosSubcapitulos por los '-'.
 * Parámetros:
 *     - i: Índice del examen en el arreglo de exámenes.
 * Retorno: Ninguno.
 */
void imprimirCapitulos(int i);


//implementacion de funciones
void listarExamenes()
{
    system("cls");
    printf("EXAMENES GUARDADOS:\n");
    FILE *archivo;
    archivo = fopen("examenes.txt", "rb");
    if (archivo == NULL || fgetc(archivo) == EOF) //si el archivo no existe o esta vacio
    {
        printf("No hay examenes guardados.\n");
        flagArchivoExamVacio = 1; //asigna 1 a la variable global flagArchivoExamVacio, variable global definida en definiciones.h
    }
    else
    {
        flagArchivoExamVacio = 0; //asigna 0 a la variable global flagArchivoExamVacio, variable global definida en definiciones.h
        crearArregloExamenes(archivo);
        imprimirExamenes(examenes);
    }
    fclose(archivo);
}
void crearArregloExamenes(FILE *archivo)
{
    char ch;
    int cont = 0;
    char numero[T], fecha[T], cantPreguntas[T], capitulosSubcapitulos[X], preguntasExamen[X];
    fseek(archivo, 0, SEEK_SET);
    while (ch != EOF)
    {
        //leer los datos de la linea, separados por coma, y guardarlos en cada variable
        copiarString(numero, archivo, ';'); 
        copiarString(fecha, archivo, ';');
        copiarString(cantPreguntas, archivo, ';');
        copiarString(capitulosSubcapitulos, archivo, ';');
        copiarString(preguntasExamen, archivo, '\n');
        //guardar los datos en la estructura
        strcpy(examenes[cont].numero, numero);
        strcpy(examenes[cont].fecha, fecha);        
        strcpy(examenes[cont].cantPreguntas, cantPreguntas);
        strcpy(examenes[cont].capitulosSubcapitulos, capitulosSubcapitulos);
        strcpy(examenes[cont].preguntas, preguntasExamen);
        cont++;
        ch = fgetc(archivo); //avanza al eof o al siguiente numero de examen
        if(ch != EOF)
        {
            fseek(archivo, -1, SEEK_CUR); //si no es eof, es un numero de examen: retrocede un caracter para que copiarString(numero, archivo) pueda leerlo correctamente (si no arranca desde el segundo caracter de la linea)
        }
    }
    cantExamenes = cont; //asigna la cantidad de examenes, variable global definida en definiciones.h
}
void imprimirExamenes()
{
    for(int i = 0; i < cantExamenes; i++)
    {
        printf("Examen %s\n", examenes[i].numero);
        printf("Fecha: %s\n", examenes[i].fecha);
        printf("Cantidad de preguntas: %s\n", examenes[i].cantPreguntas);
        imprimirCapitulos(i);
        printf("\n------------------------------------------------------------------------------------------------------------------------\n");
    }
}
void imprimirCapitulos(int i)
{
        // Crear arreglo de strings para los capitulos y subcapitulos
        char capitulos[X][X];
        char temp[X];
        strcpy(temp, examenes[i].capitulosSubcapitulos);
        int numCapitulos = 0;
        // Separar examenes[i].capitulosSubcapitulos por los '-' y guardar los strings en el arreglo
        char *token = strtok(temp, "-");
        while (token != NULL && numCapitulos < X)
        {
            strcpy(capitulos[numCapitulos], token);
            numCapitulos++;
            token = strtok(NULL, "-");
        }
        
        // Imprimir los capitulos y subcapitulos
        printf("Capitulos y subcapitulos: ");
        for (int j = 0; j < numCapitulos; j++)
        {
            printf("\n\t%s", capitulos[j]);
        }
}