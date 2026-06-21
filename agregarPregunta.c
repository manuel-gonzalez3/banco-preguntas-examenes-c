#include "definiciones.h"
#include "datosComunes.h"

// Declaración de funciones
/**
 * Agrega una nueva pregunta.
 */
void nuevaPregunta(); // Función para agregar una nueva pregunta

/**
 * Obtiene el número de la última pregunta y lo incrementa.
 * 
 * @param nueva Puntero a la estructura de la nueva pregunta.
 * @param archivo Archivo de preguntas.
 */
void obtenerNumeroPregunta(struct Pregunta *nueva, FILE *archivo); 

/**
 * Ingresa los datos de una nueva pregunta.
 * 
 * @param nueva Puntero a la estructura de la nueva pregunta.
 */
void ingresoPregunta(struct Pregunta *nueva);

/**
 * Guarda una pregunta en un archivo.
 * 
 * @param nueva Puntero a la estructura de la nueva pregunta.
 * @param archivo Archivo de preguntas.
 */
void guardarPregunta(struct Pregunta *nueva, FILE *archivo); 

/**
 * Imprime los datos de una pregunta.
 * 
 * @param nueva Puntero a la estructura de la nueva pregunta.
 */
void imprimirPregunta(struct Pregunta *nueva); 

// Definición de funciones

void nuevaPregunta()
{
    // Función principal para agregar una nueva pregunta
    printf("AGREGAR PREGUNTA\n");
    FILE *archivo;
    archivo = fopen("preguntas.txt", "ab+");
    struct Pregunta nueva;
    obtenerNumeroPregunta(&nueva, archivo); // Leer el número de la última pregunta y sumarle 1
    ingresoPregunta(&nueva); // Ingresar los datos de la pregunta
    guardarPregunta(&nueva, archivo); // Guardar la pregunta en el archivo
    
    printf("PREGUNTA GUARDADA:\n");
    imprimirPregunta(&nueva); // Imprimir la pregunta
    system("pause");
    fclose(archivo);
}

void obtenerNumeroPregunta(struct Pregunta *nueva, FILE *archivo)
{
    // Función para obtener el número de la última pregunta y sumarle 1, o asignar 1 si es la primera pregunta
    char ch;
    long pos;
    char numero[T];
    int i = 0;
    fseek(archivo, 0, SEEK_END); // Se posiciona al final del archivo
    if (ftell(archivo) == 0) // Si el archivo está vacío, asigna el número 1
    {
        strcpy(nueva->numero, "1");
    }
    else
    {
        fseek(archivo, -2, SEEK_END); // Retrocede dos caracteres para evitar el salto de línea al final del archivo
        pos = ftell(archivo);
        while (pos > 0) // Recorre el archivo hacia atrás hasta encontrar el comienzo de la última línea
        {
            fseek(archivo, --pos, SEEK_SET);
            ch = fgetc(archivo);
            if (ch == '\n')
            {
                break;
            }
        }
        if (pos > 0) // Si no está en el comienzo del archivo, se posiciona en el siguiente caracter
        {
            fseek(archivo, ++pos, SEEK_SET);
        }
        else
        {
            fseek(archivo, 0, SEEK_SET); // Si está en el comienzo del archivo, se posiciona en el comienzo
        }
        ch = fgetc(archivo);
        while (ch != ';') // Recorre la línea hasta encontrar el punto y coma
        {
            if (i < T-1) // Asegura que no se exceda el tamaño del buffer
            {
                numero[i] = ch; // Almacena el caracter leído en 'numero'
                i++;
            }
            ch = fgetc(archivo); // Lee el siguiente caracter
        }
        numero[i] = '\0'; // Agrega el carácter nulo al final del buffer
        int num = atoi(numero); // Convierte el número de la última pregunta a entero para incrementarlo
        sprintf(nueva->numero, "%i", num + 1); // Convierte el número de la nueva pregunta a string
    }
}


void ingresoPregunta(struct Pregunta *nueva) //ingresar los datos de la pregunta 
{
    char numCap[T], numSubcap[T], nombCap[X], numSubCap[T], nombSubcap[X], preg[N], opc[C][T], resp;
    int i;
    while(1)
    {
        printf("Ingrese el numero del capitulo: ");
        scanf("%s", &numCap);
        fflush(stdin);
        for(i = 0; i < strlen(numCap); i++) //recorrer el string
        {
            if (isdigit(numCap[i]) == 0 || atoi(numCap) < 0) //chequear que todo el string es numero y si es positivo
            {
                printf("Numero invalido\n");
                break;
            }
        }
        if(numCap[i] == '\0') //si llega al final del string, es un numero valido
        {
            break;
        }
    }
    while(1)
    {
        printf("Ingrese el nombre del capitulo: ");
        fgets(nombCap, X, stdin); //se usa fgets para poder leer espacios
        nombCap[strcspn(nombCap, "\n")] = 0; //quitar el salto de linea que la fc fgets agrega al final
        if (strlen(nombCap) != 0)
        {
            break;
        }
        else
        {
            printf("Nombre invalido\n");
        }
    }
    while (1) 
    {
        printf("Ingrese el numero del subcapitulo: ");
        scanf("%s", numSubcap);
        fflush(stdin);
        
        int contPuntos = 0; // Contador de puntos decimales
        for (i = 0; i < strlen(numSubcap); i++) // Recorrer el string
        { 
            if (numSubcap[i] == '.') 
            {
                contPuntos++;
            } else if (!isdigit(numSubcap[i])) 
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

        if (i == strlen(numSubcap) && contPuntos <= 1) 
        {
            if (atof(numSubcap) >= 0) 
            { // Verificar que sea un número positivo
                break;
            } else 
            {
                printf("Numero invalido\n");
            }
        }
    }
    while(1)
    {
        printf("Ingrese el nombre del subcapitulo: ");
        fgets(nombSubcap, X, stdin); //se usa fgets para poder leer espacios
        nombSubcap[strcspn(nombSubcap, "\n")] = 0; //quitar el salto de linea que la fc fgets agrega al final
        if (strlen(nombSubcap) != 0)
        {
            break;
        }
        else
        {
            printf("Nombre invalido\n");
        }
    }
    while(1)
    {
        printf("Ingrese la pregunta: ");
        fgets(preg, N, stdin); //se usa fgets para poder leer espacios
        preg[strcspn(preg, "\n")] = 0; //quitar el salto de linea que la fc fgets agrega al final
        if (strlen(preg) != 0)
        {
            break;
        }
        else
        {
            printf("Pregunta invalida\n");
        }
    }
    for(int i = 0; i < C; i++)
    {
        while(1)
        {
            printf("Ingrese la opcion %c: ", (char)(65 + i)); //65 es el valor ascii de la letra A, de ahi hasta D
            fgets(opc[i], T, stdin); //se usa fgets para poder leer espacios
            opc[i][strcspn(opc[i], "\n")] = 0; //quitar el salto de linea que la fc fgets agrega al final
            if (strlen(opc[i]) != 0)
            {
                break;
            }
            else
            {
                printf("Opcion invalida\n");
            }
        }
    }
    while(1)
    {
        printf("Ingrese la respuesta: ");
        scanf("%c", &resp);
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
    strcpy(nueva->numeroCapitulo, numCap); //guardar el numero del capitulo
    strcpy(nueva->nombreCapitulo, nombCap); //guardar el nombre del capitulo
    strcpy(nueva->numeroSubcapitulo, numSubcap); //guardar el numero del subcapitulo
    strcpy(nueva->nombreSubcapitulo, nombSubcap); //guardar el nombre del subcapitulo
    strcpy(nueva->pregunta, preg);
    for(int i = 0; i < C; i++)
    {
        strcpy(nueva->opciones[i], opc[i]);
    }
    nueva->respuesta = toupper(resp);
}

void guardarPregunta(struct Pregunta *nueva, FILE *archivo) //concatenar los datos en una linea y guardarla en el archivo
{
    char linea[N]; //linea que se va a guardar en el archivo
    char string_resp[2]; //string para guardar la respuesta, no se puede concatenar string con caracter
    string_resp[0] = nueva->respuesta; //guardar la respuesta en el string
    string_resp[1] = '\0'; //agregar el caracter nulo al final del string para poder concatenar
    strcpy(linea, nueva->numero); //concatenar el numero de la pregunta
    strcat(linea, ";");
    strcat(linea, nueva->numeroCapitulo);
    strcat(linea, ";");
    strcat(linea, nueva->nombreCapitulo);
    strcat(linea, ";");
    strcat(linea, nueva->numeroSubcapitulo);
    strcat(linea, ";");
    strcat(linea, nueva->nombreSubcapitulo);
    strcat(linea, ";");
    strcat(linea, nueva->pregunta);
    strcat(linea, ";");
    for(int i = 0; i < C; i++)
    {
        strcat(linea, nueva->opciones[i]);
        strcat(linea, ";");
    }
    strcat(linea, string_resp);
    strcat(linea, "\n");
    fseek(archivo, 0, SEEK_END); //posicionarse al final del archivo
    fputs(linea, archivo); //guardar la linea al final del archivo
}

void imprimirPregunta(struct Pregunta *nueva) //mostrar los datos de la pregunta
{
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("NUMERO DE PREGUNTA: %s\t", nueva->numero);
    printf("CAPITULO: %s - %s\t", nueva->numeroCapitulo, nueva->nombreCapitulo);
    printf("SUBCAPITULO: %s - %s\t", nueva->numeroSubcapitulo, nueva->nombreSubcapitulo);
    printf("PREGUNTA: %s\t", nueva->pregunta);
    for(int i = 0; i < C; i++)
    {
        printf("OPCION %c: %s\t", (char)(65 + i), nueva->opciones[i]);
    }
    printf("RESPUESTA CORRECTA: %c", nueva->respuesta);
    printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
}
