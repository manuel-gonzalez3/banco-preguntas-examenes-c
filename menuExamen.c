#include "definiciones.h"
#include "datosComunes.h"
#include "crearExamen.c"

int cantCapitulos = 0; 
int cantPreguntasExamen = 0;


/**
 * @brief Función que crea un arreglo de estructuras de tipo Capitulo y Subcapitulo a partir de un archivo.
 * 
 * @param capitulos Arreglo de estructuras de tipo Capitulo.
 * @param archivo Puntero al archivo que contiene los datos de los capitulos y subcapitulos.
 */
void crearArregloCapitulosSubcapitulos(struct Capitulo capitulos[N], FILE *archivo);

/**
 * @brief Función que permite ingresar los datos de los capitulos y subcapitulos.
 * 
 * @param capitulos Arreglo de estructuras de tipo Capitulo.
 * @param flagIngresoDato Puntero a la variable que indica si se ingresaron los datos o no.
 */
void ingresoDatos(struct Capitulo capitulos[N], int *flagIngresoDato);

/**
 * @brief Función que permite seleccionar un capitulo del arreglo de capitulos.
 * 
 * @param capitulos Arreglo de estructuras de tipo Capitulo.
 * @param numCap Puntero a la variable que almacenará el número del capitulo seleccionado.
 * @param indiceCapitulo Puntero a la variable que almacenará el índice del capitulo seleccionado.
 */
void seleccionarCapitulo(struct Capitulo capitulos[N], char *numCap, int *indiceCapitulo);

/**
 * @brief Función que permite seleccionar un subcapitulo del arreglo de subcapitulos de un capitulo seleccionado.
 * 
 * @param capitulos Arreglo de estructuras de tipo Capitulo.
 * @param indiceCapitulo Índice del capitulo seleccionado.
 * @param numSub Puntero a la variable que almacenará el número del subcapitulo seleccionado.
 * @param cantPreguntasCapitulos Puntero a la variable que almacenará la cantidad de preguntas del capitulo seleccionado.
 * @param flagIngresoDato Puntero a la variable que indica si se ingresaron los datos o no.
 */
void seleccionarSubcapitulo(struct Capitulo capitulos[N], int indiceCapitulo, char *numSub, int *cantPreguntasCapitulos, int *flagIngresoDato);

/**
 * @brief Función que solicita al usuario la cantidad de preguntas para un capitulo seleccionado.
 * 
 * @param cantPreguntasCapitulos Cantidad de preguntas del capitulo seleccionado.
 */
void pedirCantidadPreguntas(int cantPreguntasCapitulos);

//implementacion de funciones

void menuExamen()
{
    int flagIngresoDato = 0;
    printf("CREAR EXAMEN\n");
    FILE *archivo = fopen("preguntas.txt", "rb");
    if (archivo == NULL || fgetc(archivo) == EOF) 
    {
        printf("No hay preguntas guardadas.\n");
        system("pause");
        return;
    }
    crearArregloCapitulosSubcapitulos(capitulos, archivo);
    ingresoDatos(capitulos, &flagIngresoDato);
    if(flagIngresoDato == 1)
    {
        crearExamen(capitulos);
        printf("Examen creado con exito.\n");
        system("pause");
    }
}

void crearArregloCapitulosSubcapitulos(struct Capitulo capitulos[N], FILE *archivo)
{
    crearArregloPreguntas(archivo);
    fclose(archivo);
    int IndiceCapitulo = 0;
    for (int i = 0; i < cantPreguntas; i++)  // Iterar sobre las preguntas
    {
        int EncontrarCapitulo = -1; // Variable para verificar si el capitulo ya fue agregado
        for (int j = 0; j < IndiceCapitulo; j++) 
        {
            if (strcmp(capitulos[j].numCapitulo, preguntas[i].numeroCapitulo) == 0) 
            {
                EncontrarCapitulo = j;
                break;
            }
        }

        if (EncontrarCapitulo == -1) // Si el capitulo no fue agregado
        {
            strcpy(capitulos[IndiceCapitulo].numCapitulo, preguntas[i].numeroCapitulo); // Agregar el capitulo
            strcpy(capitulos[IndiceCapitulo].nombreCapitulo, preguntas[i].nombreCapitulo); // Agregar el nombre del capitulo
            capitulos[IndiceCapitulo].cantSubcapitulos = 0; // Inicializar la cantidad de subcapitulos
            capitulos[IndiceCapitulo].cantPreguntas = 0; // Inicializar la cantidad de preguntas
            capitulos[IndiceCapitulo].seleccionado = 0; // Inicializar la seleccion del capitulo
            capitulos[IndiceCapitulo].agregado = 0; // Inicializar la agregacion del capitulo
            EncontrarCapitulo = IndiceCapitulo; 
            IndiceCapitulo++;
        }

        int EncontrarSubcapitulo = -1; // Variable para verificar si el subcapitulo ya fue agregado
        for (int k = 0; k < capitulos[EncontrarCapitulo].cantSubcapitulos; k++)  // Iterar sobre los subcapitulos
        {
            if (strcmp(capitulos[EncontrarCapitulo].subcapitulos[k].numSubcapitulo, preguntas[i].numeroSubcapitulo) == 0) // Verificar si el subcapitulo ya fue agregado
            {
                EncontrarSubcapitulo = k; 
                capitulos[EncontrarCapitulo].subcapitulos[k].cantPreguntas++; // Aumentar la cantidad de preguntas del subcapitulo
                break;
            }
        }

        if (EncontrarSubcapitulo == -1) // Si el subcapitulo no fue agregado
        {
            int IndiceSubCapitulo = capitulos[EncontrarCapitulo].cantSubcapitulos; // Obtener el indice del subcapitulo
            strcpy(capitulos[EncontrarCapitulo].subcapitulos[IndiceSubCapitulo].numSubcapitulo, preguntas[i].numeroSubcapitulo); // Agregar el subcapitulo
            strcpy(capitulos[EncontrarCapitulo].subcapitulos[IndiceSubCapitulo].nombreSubcapitulo, preguntas[i].nombreSubcapitulo); // Agregar el nombre del subcapitulo
            capitulos[EncontrarCapitulo].cantSubcapitulos++; // Aumentar la cantidad de subcapitulos del capitulo
            capitulos[EncontrarCapitulo].subcapitulos[IndiceSubCapitulo].cantPreguntas = 1; // Inicializar la cantidad de preguntas del subcapitulo
            capitulos[EncontrarCapitulo].subcapitulos[IndiceSubCapitulo].seleccionado = 0; // Inicializar la seleccion del subcapitulo
        }
    }

    cantCapitulos = IndiceCapitulo; // Actualizar la cantidad de capitulos
    for(int i = 0; i < cantCapitulos; i++)
    {
        capitulos[i].cantPreguntas = 0;
        for(int j = 0; j < capitulos[i].cantSubcapitulos; j++)
        {
            capitulos[i].cantPreguntas += capitulos[i].subcapitulos[j].cantPreguntas; // Calcular la cantidad de preguntas del capitulo a partir de los subcapitulos
        }
    }
}

void ingresoDatos(struct Capitulo capitulos[N], int *flagIngresoDato)
{
    char numCap[T], numSub[T]; //variables para almacenar el numeros de capitulo y subcapitulo que ingresara el usuario
    int indiceCapitulo = -1;
    int cantPreguntasCapitulos = 0; // Variable para almacenar la cantidad de preguntas de los capitulos seleccionados
    *flagIngresoDato = 0; 
    do
    {
        for(int i = 0; i < cantCapitulos; i++) // Iterar sobre los capitulos para marcarlos como agregados si todos los subcapitulos fueron agregados
        {
            int capituloAgregado = 1; // Variable para verificar si el capitulo fue agregado entero
            for(int j = 0; j < capitulos[i].cantSubcapitulos; j++)
            {
                if(capitulos[i].subcapitulos[j].seleccionado == 0) // Verificar si todos los subcapitulos fueron agregados
                {
                    capituloAgregado = 0; // Si no fueron agregados todos los subcapitulos, el capitulo no fue agregado entero
                    break;
                }
            }
            if(capituloAgregado == 1) // Si el capitulo fue agregado entero
            {
                capitulos[i].agregado = 1; // Marcar el capitulo como agregado
            }
        }
        seleccionarCapitulo(capitulos, numCap, &indiceCapitulo);
        if (strcmp(numCap, "*") == 0) 
        {
            break;
        }
        do
        {
            seleccionarSubcapitulo(capitulos, indiceCapitulo, numSub, &cantPreguntasCapitulos, flagIngresoDato);
        } while(strcmp(numSub, "*") != 0 && strcmp(numSub, "T") != 0);
    } while(strcmp(numCap, "*") != 0);

    if(*flagIngresoDato == 1)    
    {
        pedirCantidadPreguntas(cantPreguntasCapitulos);
    }
}

void seleccionarCapitulo(struct Capitulo capitulos[N], char *numCap, int *indiceCapitulo)
{
    system("cls");
    printf("CAPITULOS\n");
    for(int i = 0; i < cantCapitulos; i++)
    {
        printf("Capitulo %s: %s\n", capitulos[i].numCapitulo, capitulos[i].nombreCapitulo);
    }
    while(1)
    {
        printf("Ingrese el numero del capitulo que desea agregar('*' Volver/Confirmar): ");
        scanf("%s", numCap);
        fflush(stdin);
        if (strcmp(numCap, "*") == 0) // Verificar si se ingreso '*' para volver
        {
            break;
        }

        for (int i = 0; i < cantCapitulos; i++)  // Iterar sobre los capitulos
        {
            if (strcmp(numCap, capitulos[i].numCapitulo) == 0)  //verificar si el capitulo existe
            {
                *indiceCapitulo = i; // Asignar el indice del capitulo
                break;
            }
        }

        if (*indiceCapitulo == -1)  
        {
            printf("El numero de capitulo ingresado no es valido.\n");
        } 
        else 
        {
            if(capitulos[*indiceCapitulo].agregado == 1) // Verificar si el capitulo fue agregado por completo
            {
                printf("El capitulo fue agregado anteriormente.\n");
            } 
            else 
            {
                break;
            }
        }
    }
}

void seleccionarSubcapitulo(struct Capitulo capitulos[N], int indiceCapitulo, char *numSub, int *cantPreguntasCapitulos, int *flagIngresoDato)
{
    int indiceSubcapitulo = -1; 
    system("cls");
    printf("SUBACAPITULOS DEL CAPITULO %s: %s\n", capitulos[indiceCapitulo].numCapitulo, capitulos[indiceCapitulo].nombreCapitulo);
    for(int i = 0; i < capitulos[indiceCapitulo].cantSubcapitulos; i++)
    {
        printf("Subcapitulo %s: %s\n", capitulos[indiceCapitulo].subcapitulos[i].numSubcapitulo, capitulos[indiceCapitulo].subcapitulos[i].nombreSubcapitulo);
    }

    while(1)
    {
        printf("Ingrese el numero del subcapitulo que desea agregar('*' Volver - 'T' Todos): ");
        scanf("%s", numSub);
        fflush(stdin);
        numSub[0] = toupper(numSub[0]); // Convertir el caracter a mayuscula para aceptar 'T' y 't'

        if (strcmp(numSub, "*") == 0) // Verificar si se ingreso '*' para volver
        {
            break;
        }

        if(strcmp(numSub, "T") != 0) 
        {
            for (int i = 0; i < capitulos[indiceCapitulo].cantSubcapitulos; i++)  // Iterar sobre los subcapitulos
            {
                if (strcmp(numSub, capitulos[indiceCapitulo].subcapitulos[i].numSubcapitulo) == 0)  //verificar si el subcapitulo existe
                {
                    indiceSubcapitulo = i;
                    break;
                }
            }

            if (indiceSubcapitulo == -1) 
            {
                printf("El numero de subcapitulo ingresado no es valido.\n");
            } 
            else //si es un subcapitulo valido
            {
                if(capitulos[indiceCapitulo].subcapitulos[indiceSubcapitulo].seleccionado == 1) //verificar si el subcapitulo fue agregado
                {
                    printf("El subcapitulo fue agregado anteriormente.\n");
                } 
                else 
                {
                    capitulos[indiceCapitulo].subcapitulos[indiceSubcapitulo].seleccionado = 1; // Marcar el subcapitulo como seleccionado
                    capitulos[indiceCapitulo].seleccionado = 1; //marcar el capitulo como seleccionado
                    *flagIngresoDato = 1; // Cambiar el flag de ingreso de datos
                    *cantPreguntasCapitulos += capitulos[indiceCapitulo].subcapitulos[indiceSubcapitulo].cantPreguntas; // Aumentar la cantidad de preguntas posible del capitulo
                    printf("Subcapitulo agregado con exito.\n");
                    system("pause");
                    break;
                }
            }
        }
        else //si se ingreso 'T' para seleccionar todos los subcapitulos
        {
            for(int i = 0; i < capitulos[indiceCapitulo].cantSubcapitulos; i++) // Iterar sobre los subcapitulos del capitulo
            {
                capitulos[indiceCapitulo].subcapitulos[i].seleccionado = 1; //marcar todos los subcapitulos como seleccionados
                *cantPreguntasCapitulos += capitulos[indiceCapitulo].subcapitulos[i].cantPreguntas; // Aumentar la cantidad de preguntas posible del capitulo
            }
            capitulos[indiceCapitulo].seleccionado = 1; //marcar el capitulo como seleccionado
            *flagIngresoDato = 1;
            printf("Todos los subcapitulos del capitulo %s fueron agregados con exito.\n", capitulos[indiceCapitulo].numCapitulo);
            system("pause");
            break;
        }
    }
}

void pedirCantidadPreguntas(int cantPreguntasCapitulos)
{
    system("cls");
    do
    {
        printf("Ingrese la cantidad de preguntas que contendra el examen: ");
        scanf("%i", &cantPreguntasExamen);
        fflush(stdin);
        if (cantPreguntasExamen <= 0 || cantPreguntasExamen > cantPreguntasCapitulos) // Verificar si la cantidad de preguntas es posible
        {
            printf("Cantidad de preguntas invalida. Ingrese un valor mayor a 0 y menor o igual al total de preguntas seleccionadas (%i).\n", cantPreguntasCapitulos);
        }
    } while (cantPreguntasExamen <= 0 || cantPreguntasExamen > cantPreguntasCapitulos);
}
