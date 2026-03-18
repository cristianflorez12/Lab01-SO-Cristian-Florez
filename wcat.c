#include <stdio.h>
#include <stdlib.h>

void printFile(const char *filename) {
    // Intentar abrir el archivo en modo lectura ("r")
    FILE *fp = fopen(filename, "r");

    // Si el archivo no se puede abrir, mostrar un mensaje de error y salir con código 1
    if (fp == NULL) {
        printf("wcat: cannot open file\n");
        exit(1);
    }

    // Buffer para almacenar líneas leídas del archivo
    char buffer[4096];

    // Leer líneas del archivo hasta el final del archivo
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    // Cerrar el archivo
    fclose(fp);
}

int main(int argc, char *argv[]) {
    /* Si no se pasan archivos, salir con codigo 0 */
    if (argc == 1) {
        exit(0);
    }

    /* Recorrer cada archivo pasado como argumento */
    for (int i = 1; i < argc; i++) {
        printFile(argv[i]);
    }

    return 0;
}
