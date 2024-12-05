#include "lectura_datos.h"
#include <string.h>
#include <stdlib.h>

#define MAXCARACTERESLINEA 100

FILE* abrir_archivo(char* ruta) {
    FILE* fichero = NULL;
    
    char* dataset_path = "datasets/";
    
    size_t tam = strlen(ruta) + strlen(dataset_path) + 1;
    char* ruta_completa = (char*)malloc(tam);
    
    strcpy(ruta_completa, dataset_path);
    strcat(ruta_completa, ruta);    

    if (ruta == NULL) {
        printf("\nError al reservar memoria\n");
        exit(1);
    } else {
        if ((fichero = fopen(ruta_completa, "r")) == NULL) {
            printf("\nError de apertura de archivo.\n");
            exit(-1);
        }
    }

    free(ruta_completa);

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