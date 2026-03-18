#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementación propia de getline
// Lee una línea completa de un archivo, sin límite fijo de tamaño
ssize_t my_getline(char **lineptr, size_t *n, FILE *fp) {
    // Validar parámetros
    if (lineptr == NULL || n == NULL || fp == NULL) return -1;

    // Tamanio inicial del buffer si aun no existe
    if (*lineptr == NULL || *n == 0) {
        *n = 128;
        *lineptr = malloc(*n);
        if (*lineptr == NULL) return -1;
    }

    size_t pos = 0;
    int ch;

    // Leer letras del archivo hasta el final del archivo
    while ((ch = fgetc(fp)) != EOF) {
        // Si el buffer se llena, duplicar su tamanio
        if (pos + 1 >= *n) {
            *n *= 2;
            char *tmp = realloc(*lineptr, *n);
            if (tmp == NULL) return -1;
            *lineptr = tmp;
        }

        // Agregar la letra leida al buffer
        (*lineptr)[pos++] = (char)ch;

        // Si se encuentra un salto de linea, terminar la lectura
        if (ch == '\n') break;
    }

    if (pos == 0) return -1;    /* EOF sin leer nada */

    // Agregar la letra nula al final del buffer
    (*lineptr)[pos] = '\0';

    // Devolver la cantidad de letras leidas
    return (ssize_t)pos;
}

void searchInStream(FILE *fp, const char *searchTerm) {
    char   *line = NULL; // Buffer para almacenar la linea leida
    size_t  len  = 0;

    // Leer lineas del archivo hasta el final del archivo
    while (my_getline(&line, &len, fp) != -1) {
        if (strstr(line, searchTerm) != NULL) {
            printf("%s", line);
        }
    }

    // Liberar memoria
    free(line);
}

int main(int argc, char *argv[]) {
    // Sin argumentos: mostrar uso correcto 
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    const char *searchTerm = argv[1];

    // Solo termino de busqueda, sin archivos -> leer de stdin
    if (argc == 2) {
        searchInStream(stdin, searchTerm);
        return 0;
    }

    // Recorrer cada archivo
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");

        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        // Buscar la palabra en el archivo
        searchInStream(fp, searchTerm);

        // Cerrar el archivo
        fclose(fp);
    }

    return 0;
}
