#include "datosComunes.h"
#include "definiciones.h"
//declaracion de funciones
/**
 * Función que muestra el menú para modificar una pregunta.
 */
void menuModificarPregunta();

/**
 * Función que solicita al usuario ingresar un dato para modificar una pregunta.
 * 
 * @param nPregunta El número de la pregunta a modificar.
 * @param dato Puntero al dato ingresado por el usuario.
 * @param flagIngresoDato Puntero a la bandera que indica si se ingresó un dato válido.
 */
void pedirDato(int nPregunta, int *dato, int *flagIngresoDato);

/**
 * Función que modifica una pregunta con el dato ingresado por el usuario.
 * 
 * @param nPregunta El número de la pregunta a modificar.
 * @param dato El dato ingresado por el usuario.
 */
void modificarPregunta(int nPregunta, int *dato);

/**
 * Función que modifica un string en una pregunta.
 * 
 * @param string El string a modificar.
 * @param tipo El tipo de dato que se espera ingresar.
 * @param validarNum Indica si se debe validar que el string sea un número válido. Es 1 si se necesita validar que el string sea un numero entero positivo, es 2 si se necesita validar que el string sea un flotante positivo.
 */
void modificarString(char *string, char *tipo, int validarNum);

/**
 * Función que actualiza el archivo con las preguntas modificadas.
 */
void actualizarArchivo();

//implementacion de funciones

void menuModificarPregunta()
{
    int nPregunta = 0, dato = 1;
    do
    {
        int flagIngresoDato = 0; //se inicia en 0 cada vez que se le muestran las preguntas al usuario, se modifica cuando ingresa una opcion de dato que no sea 0
        listarPreguntas(); //se listan las preguntas del archivo, esta funcion genera el arreglo de preguntas que se usa en este archivo
        if(flagArchivoPregVacio == 0)
        {
            while(1)
            {
                printf("Ingrese el numero de la pregunta que desea modificar(0-Volver): ");
                scanf("%i", &nPregunta);
                fflush(stdin);
                if(nPregunta >= 0 && nPregunta <= cantPreguntas)
                {
                    break;
                }
                else
                {
                    printf("Numero invalido\n");
                }
            }
            if(nPregunta != 0)
            {
                do
                {
                    system("cls");
                    pedirDato(nPregunta, &dato, &flagIngresoDato); //pedir el dato a modificar
                    modificarPregunta(nPregunta, &dato); //modificar el dato en el arreglo de preguntas
                } while(dato != 0); //el archivo se actualiza solo si se modifica algun dato y cuando se confirma con 0
                if(flagIngresoDato == 1) //guardar solo si se modifico algun dato, si no vuelve a mostrar las preguntas sin hacer nada
                {
                    actualizarArchivo();
                    printf("PREGUNTA MODIFICADA\n");
                    imprimirPregunta(&preguntas[nPregunta-1]);
                    printf("\n");

                }
            }
        }
        else
        {
            system("pause");
            break;
        }
    } while(nPregunta != 0);
}
void pedirDato(int nPregunta, int *dato, int *flagIngresoDato)
{
    while(1)
    {
        imprimirPregunta(&preguntas[nPregunta-1]); //funcion de agregarPregunta.c, imprime una unica estructura de pregunta
        printf("¿Que dato desea modificar de la pregunta %s?\n", preguntas[nPregunta-1].pregunta);
        printf("1. Numero Capitulo\n");
        printf("2. Nombre Capitulo\n");
        printf("3. Numero Subcapitulo\n");
        printf("4. Nombre Subcapitulo\n");
        printf("5. Pregunta\n");
        printf("6. Opcion A\n");
        printf("7. Opcion B\n");
        printf("8. Opcion C\n");
        printf("9. Opcion D\n");
        printf("10. Respuesta\n");
        printf("0. Volver-Confirmar\n");
        printf("Ingrese una opcion: ");
        scanf("%i", dato);
        fflush(stdin);
        if(*dato >= 0 && *dato <= 10)
        {
            if(*dato != 0) //si no es 0, se modificara un dato, se cambia el flag
            {
                *flagIngresoDato = 1;
            }
            break;
        }
        else
        {
            printf("Opcion invalida\n");
        }
    }
}

//cambiar el dato en el arreglo de preguntas
void modificarPregunta(int nPregunta, int *dato)
{
    char numCap[T], nombCap[T], numSub[T], nombSub[T], preg[T], opc[C][T], resp; //variables auxiliares para guardar los datos de la pregunta
    strcpy(numCap, preguntas[nPregunta-1].numeroCapitulo); //se copian los datos de la pregunta a variables auxiliares
    strcpy(nombCap, preguntas[nPregunta-1].nombreCapitulo);
    strcpy(numSub, preguntas[nPregunta-1].numeroSubcapitulo);
    strcpy(nombSub, preguntas[nPregunta-1].nombreSubcapitulo);
    strcpy(preg, preguntas[nPregunta-1].pregunta);
    for(int i = 0; i < C; i++)
    {
        strcpy(opc[i], preguntas[nPregunta-1].opciones[i]);
    }
    resp = preguntas[nPregunta-1].respuesta;
    system("cls");
    switch(*dato) //se modifica el dato segun la opcion ingresada
    {
        case 1:
            printf("Numero capitulo actual: %s\n", numCap);
            modificarString(numCap, "numero de capitulo", 1);
            strcpy(preguntas[nPregunta-1].numeroCapitulo, numCap); //se copian los datos de las variables auxiliares a la estructura de pregunta
            break;
        case 2:
            printf("Nombre capitulo actual: %s\n", nombCap);
            modificarString(nombCap, "nombre de capitulo", 0);
            strcpy(preguntas[nPregunta-1].nombreCapitulo, nombCap);
            break;
        case 3:
            printf("Numero subcapitulo actual: %s\n", numSub);
            modificarString(numSub, "numero de subcapitulo", 2);
            strcpy(preguntas[nPregunta-1].numeroSubcapitulo, numSub);
            break;
        case 4:
            printf("Nombre subcapitulo actual: %s\n", nombSub);
            modificarString(nombSub, "nombre de subcapitulo", 0);
            strcpy(preguntas[nPregunta-1].nombreSubcapitulo, nombSub);
            break;
        case 5:
            printf("Pregunta actual: %s\n", preg);
            modificarString(preg, "pregunta", 0);
            strcpy(preguntas[nPregunta-1].pregunta, preg);
            break;
        case 6:
            printf("Opcion A actual: %s\n", opc[0]);
            modificarString(opc[0], "opcion A", 0);
            strcpy(preguntas[nPregunta-1].opciones[0], opc[0]);
            break;
        case 7:
            printf("Opcion B actual: %s\n", opc[1]);
            modificarString(opc[1], "opcion B", 0);
            strcpy(preguntas[nPregunta-1].opciones[1], opc[1]);
            break;
        case 8: 
            printf("Opcion C actual: %s\n", opc[2]);
            modificarString(opc[2], "opcion C", 0);
            strcpy(preguntas[nPregunta-1].opciones[2], opc[2]);
            break;
        case 9: 
            printf("Opcion D actual: %s\n", opc[3]);
            modificarString(opc[3], "opcion D", 0);
            strcpy(preguntas[nPregunta-1].opciones[3], opc[3]);
            break;
        case 10: 
            printf("Respuesta actual: %c\n", resp);
            while(1)
            {
                printf("Ingrese la respuesta: ");
                scanf(" %c", &resp); 
                fflush(stdin);
                if (isalpha(resp) && (toupper(resp) >= 'A' && toupper(resp) <= 'D')) //chequear si es una letra y si es una de las opciones
                {
                    break;
                }
                else
                {
                    printf("Respuesta invalida\n");
                }
            }
            preguntas[nPregunta-1].respuesta = resp; //caracter unico, no string
            break;
        case 0:
            break;
    }
}

//estructura que se repite en cada opcion de modificarDato
void modificarString(char *string, char *tipo, int validarNum) 
{
    while(1)
    {
        printf("Ingrese el/la nuevo/a %s: ", tipo);
        fgets(string, T, stdin); //se usa fgets para poder leer espacios
        string[strcspn(string, "\n")] = 0; //quitar el salto de linea que la fc fgets agrega al final
        if (strlen(string) != 0)
        {
            if(validarNum == 1) //si se necesita validar que el string sea un numero entero positivo
            {
                int i;
                for(i = 0; i < strlen(string); i++) //recorrer el string
                {
                    if (isdigit(string[i]) == 0 || atoi(string) < 0) //chequear que todo el string es numero y si es positivo
                    {
                        printf("Numero invalido\n"); //si no es numero
                        break;
                    }
                }
                if(string[i] == '\0') //si se recorrio todo el string y no se encontro un caracter invalido
                {
                    break;
                }
            }
            else if(validarNum == 2) //si se necesita validar que el string sea un flotante positivo
            {
                int i;
                int contPuntos = 0; // Contador de puntos decimales
                for (i = 0; i < strlen(string); i++) // Recorrer el string
                { 
                    if (string[i] == '.') 
                    {
                        contPuntos++;
                    } else if (!isdigit(string[i])) 
                    {
                        printf("Numero invalido\n");
                        break;
                    }
                    if (contPuntos > 1) 
                    { // Más de un punto decimal
                        printf("Numero invalido\n");
                        break;
                    }
                }

                if (i == strlen(string) && contPuntos <= 1) 
                {
                    if (atof(string) >= 0) 
                    { // Verificar que sea un número positivo
                        break;
                    } else 
                    {
                        printf("Numero invalido\n");
                    }
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            printf("Entrada invalida\n", tipo); //si el string esta vacio
        }
    }
}

//sobreescritura del archivo con las preguntas modificadas
void actualizarArchivo()
{
    FILE *archivo;
    archivo = fopen("preguntas.txt", "wb");
    for(int i = 0; i < cantPreguntas; i++)
    {
        guardarPregunta(&preguntas[i], archivo); //funcion de agregarPregunta.c, guarda una estructura de pregunta en el archivo
    }
    fclose(archivo);
}