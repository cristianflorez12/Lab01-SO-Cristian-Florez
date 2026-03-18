#include <stdio.h>
#include <stdlib.h>

// Escribe el bloque comprimido en el conteo int char
void writeRLE(int count, char ch) {
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&ch,    sizeof(char), 1, stdout);
}

//procesa un archivo y aplica compresion
void compressStream(FILE *fp, int *prevChar, int *count) {
    int ch;

    //leer letra por letra del archivo
    while ((ch = fgetc(fp)) != EOF) {
        if (*prevChar == -1) {
            // Primera letra del primer archivo
            *prevChar = ch;
            *count    = 1;
        } else if (ch == *prevChar) {
            // Misma letra: incrementar repeticiones
            (*count)++;
        } else {
            // Nueva letra: escribir repeticiones anterior y reiniciar
            writeRLE(*count, (char)*prevChar);
            *prevChar = ch;
            *count    = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    // Sin argumentos: mostrar uso correcto
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    int prevChar = -1;  // -1 indica que aun no hemos leido nada
    int count    = 0;

    // Recorrer cada archivo
    for (int i = 1; i < argc; i++) {
        // Abrir el archivo
        FILE *fp = fopen(argv[i], "r");

        // Si el archivo no se puede abrir, mostrar un mensaje de error y salir con codigo 1
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        // Comprimir el archivo
        compressStream(fp, &prevChar, &count);

        // Cerrar el archivo
        fclose(fp);
    }

    // Escribir la ultima repeticion pendiente
    if (prevChar != -1) {
        writeRLE(count, (char)prevChar);
    }

    return 0;
}
