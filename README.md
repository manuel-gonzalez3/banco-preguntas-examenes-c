# Banco de Preguntas y Exámenes (C)

Aplicación de consola en **C** para administrar un banco de preguntas, generar
exámenes a partir de él y corregirlos. Desarrollada como trabajo final de la materia
**Lenguajes Estructurados**.

## Funcionalidades

- **Banco de preguntas**: agregar, modificar, eliminar y listar preguntas.
- **Exámenes**: crear exámenes seleccionando preguntas del banco y listarlos.
- **Corrección**: corregir exámenes rendidos.
- Persistencia en archivos de texto (`preguntas.txt`, `examenes.txt`).

## Diseño

Código **modular**: cada operación vive en su propio archivo `.c`, coordinados por
menús (`main.c` → `menuBanco.c` / `menuExamen.c` / `menuCorreccion.c`). Las estructuras
y constantes compartidas están en los headers `datosComunes.h` y `definiciones.h`.

```
main.c              # menú principal
menuBanco.c         # ABM de preguntas
menuExamen.c        # creación de exámenes
menuCorreccion.c    # corrección de exámenes
agregarPregunta.c modificarPregunta.c eliminarPregunta.c listarPreguntas.c
crearExamen.c listarExamenes.c
datosComunes.h definiciones.h
preguntas.txt examenes.txt   # datos de ejemplo
```

## Compilar y ejecutar

`main.c` incluye los demás módulos vía `#include`, así que se compila un único archivo:

```bash
gcc main.c -o banco
./banco
```

> El código usa `system("cls")` (limpiar pantalla en Windows). En Linux/Mac
> reemplazar por `system("clear")` si se desea el mismo comportamiento.

## Autor

Manuel González Janin
