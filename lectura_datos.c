#include "lectura_datos.h"
#include <stdlib.h>
#define MAXCARACTERESLINEA 100

FILE* abrir_archivo(char* ruta) {
    FILE* fichero = NULL;

    if ((fichero = fopen(ruta, "r")) == NULL) {
        printf("\nError de apertura de archivo.\n");
        exit(-1);
    }
    return fichero;
}

void cerrar_archivo(FILE* fichero) {
    fclose(fichero);
}

char* leer_linea(FILE* fichero) {
    if (fichero != NULL) {
        char* linea = (char*)malloc(MAXCARACTERESLINEA*sizeof(char));
        if (linea != NULL) {
            if (fgets(linea, MAXCARACTERESLINEA, fichero)) {
                return linea;
            }
        }
    }
    return NULL;
}