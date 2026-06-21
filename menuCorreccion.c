#include "definiciones.h"
#include "datosComunes.h"
#include "listarExamenes.c"
/**
 * @brief Función que muestra el menú de corrección de exámenes.
 * 
 */
void menuCorreccion();

/**
 * @brief Función que corrige un examen específico.
 * 
 * @param numExamen El número del examen a corregir.
 */
void corregirExamen(int numExamen);

/**
 * @brief Función que separa las preguntas de un examen específico, ya que estan guardadas todas juntas en la estructura.
 * 
 * @param numExamen El número del examen a separar las preguntas.
 * @param stringNumPregunta El arreglo de cadenas que almacenará las preguntas separadas.
 */
void separarPreguntasExamen(int numExamen, char stringNumPregunta[atoi(examenes[numExamen-1].cantPreguntas)][X]);

/**
 * @brief Función que muestra la nota obtenida en un examen.
 * 
 * @param nota La nota obtenida en el examen.
 * @param correctas El arreglo de respuestas correctas.
 * @param cantPreguntas La cantidad de preguntas del examen.
 */
void mostrarNota(float nota, int correctas[], int cantPreguntas);

//implementacion de funciones
void menuCorreccion()
{
    int numExamen =0;
    do
    {
        system("cls");
        printf("CORREGIR EXAMEN\n");
        listarExamenes();
        if(flagArchivoExamVacio == 0)
        {
            while(1)
            {
                printf("Ingrese el numero de examen que desea corregir(0-Volver): ");
                scanf("%i", &numExamen);
                fflush(stdin);
                if(numExamen >= 0 && numExamen <= cantExamenes)
                {
                    break;
                }
                else
                {
                    printf("Numero invalido\n");
                }
            }
            if(numExamen != 0)
            {
                corregirExamen(numExamen);
            }
        }
        else
        {
            system("pause");
            break;
        }
    }while(numExamen != 0);
}
void corregirExamen(int numExamen)
{
    float nota = 0;
    int correctas[atoi(examenes[numExamen-1].cantPreguntas)]; //arreglo para guardar si la respuesta es correcta o no
    system("cls");
    printf("EXAMEN %s\n", examenes[numExamen-1].numero);
    printf("Capitulos y subcapitulos: ");
    imprimirCapitulos(numExamen-1);
    printf("\n");
    printf("Preguntas:\n");
    FILE *archivo = fopen("preguntas.txt", "rb");
    crearArregloPreguntas(archivo);
    fclose(archivo);
    char stringNumPregunta[atoi(examenes[numExamen-1].cantPreguntas)][X]; //arreglo para guardar los numeros de las preguntas separados
    separarPreguntasExamen(numExamen, stringNumPregunta); //separar las preguntas del examen

    for(int i = 0; i < atoi(examenes[numExamen-1].cantPreguntas); i++) //iterar por las preguntas del examen
    {
        for(int j = 0; j < cantPreguntas; j++) //iterar por las preguntas del archivo
        {
            if(strcmp(preguntas[j].numero, stringNumPregunta[i]) == 0) //si el numero de la pregunta del archivo es igual al numero de la pregunta del examen imprime la pregunta y las opciones
            { 
                printf("\n%i-%s\n", i+1, preguntas[j].pregunta);
                for(int k = 0; k < C; k++)
                {
                    printf("%c) %s\n", 'A'+k, preguntas[j].opciones[k]);
                }
                char respuesta;
                while(1)
                {
                    printf("\nIngrese la respuesta: ");
                    scanf("%c", &respuesta);
                    fflush(stdin);
                    respuesta = toupper(respuesta);
                    if (isalpha(respuesta) && (respuesta >= 'A' && respuesta <= 'D')) //chequear si es una letra y si es una de las opciones
                    {
                        break;
                    }
                    else
                    {
                        printf("Respuesta invalida\n");
                    }
                }
                if(respuesta == preguntas[j].respuesta) //si la respuesta es correcta suma 1 a la nota y guarda 1 en el arreglo correctas
                {
                    correctas[i] = 1;
                    nota++;
                }
                else //si la respuesta es incorrecta guarda 0 en el arreglo correctas
                {
                    correctas[i] = 0;
                }
            }
        }
    }
    nota = (nota/atoi(examenes[numExamen-1].cantPreguntas))*10;
    mostrarNota(nota, correctas, atoi(examenes[numExamen-1].cantPreguntas));
}

void separarPreguntasExamen(int numExamen, char stringNumPregunta[atoi(examenes[numExamen-1].cantPreguntas)][X])
{
    char temp[X]; //arreglo auxiliar para guardar las preguntas
    strcpy(temp, examenes[numExamen-1].preguntas); //copiar las preguntas del examen en el arreglo auxiliar
    int numCapitulos = 0; //contador para guardar las preguntas en el arreglo

    // Separar examenes[i].preguntas por las comas y guardar los strings en el arreglo
    char *token = strtok(temp, ",");
    while (token != NULL && numCapitulos < X) //mientras haya preguntas y no se haya llegado al limite del arreglo
    {
        strcpy(stringNumPregunta[numCapitulos], token); 
        numCapitulos++;
        token = strtok(NULL, ","); //siguiente pregunta
    }
}
void mostrarNota(float nota, int correctas[], int cantPreguntas)
{
    printf("--------------------\n");
    printf("Nota: %.2f\n", nota);
    printf("Respuestas:\n\t");
    for(int i = 0; i < cantPreguntas; i++)
    {
        if(correctas[i] == 1)
        {
            printf("%i CORRECTA\n", i+1);
        }
        else
        {
            printf("%i INCORRECTA\n", i+1);
        }
    }
    printf("\n");
    system("pause");
}