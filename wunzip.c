#include <stdio.h>
#include <stdlib.h>

// Descomprime un archivo y lo imprime
void decompressStream(FILE *fp) {
    int  count;
    char ch;

    // Leer pares (int, char) hasta el fin del archivo.
    while (fread(&count, sizeof(int), 1, fp) == 1) {
        // Leer la letra del par
        if (fread(&ch, sizeof(char), 1, fp) != 1) {
            // Archivo corrupto: falta la letra del par
            fprintf(stderr, "wunzip: archivo comprimido invalido\n");
            exit(1);
        }

        // Imprimir la letra 'count' veces
        for (int i = 0; i < count; i++) {
            putchar(ch);
        }
    }
}

int main(int argc, char *argv[]) {
    // Sin argumentos: mostrar uso correcto
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    // Recorrer cada archivo
    for (int i = 1; i < argc; i++) {
        // Abrir el archivo en modo binario
        FILE *fp = fopen(argv[i], "rb");

        // Si el archivo no se puede abrir, mostrar un mensaje de error y salir con codigo 1
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        // Descomprimir el archivo
        decompressStream(fp);

        // Cerrar el archivo
        fclose(fp);
    }

    return 0;
}
