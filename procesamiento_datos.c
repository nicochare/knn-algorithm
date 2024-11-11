#include "procesamiento_datos.h"
#include "lectura_datos.h"
#include <string.h>
#include <stdlib.h>
#define CANTLINEAS 100000

void guardar_registro(char* linea_leida, Registro* datos, int i) {
    char* token = strtok(linea_leida, ",");
    if (strcmp(token, "Male") == 0) {
        datos[i].gender = 0;
    }
    else {
        datos[i].gender = 1;
    }

    token = strtok(NULL, ",");
    datos[i].age = atof(token);

    token = strtok(NULL, ",");
    datos[i].hypertension = atoi(token);

    token = strtok(NULL, ",");
    datos[i].heart_disease = atoi(token);

    token = strtok(NULL, ",");
    int smoking_history;

    if (strcmp(token, "current") == 0) {
        smoking_history = 1;
    }
    else if (strcmp(token, "former") == 0) {
        smoking_history = 2;
    }
    else if (strcmp(token, "No info") == 0) {
        smoking_history = 3;
    }
    else if (strcmp(token, "never") == 0) {
        smoking_history = 4;
    }
    else if (strcmp(token, "not current") == 0) {
        smoking_history = 5;
    }
    else {
        smoking_history = 6;
    }

    datos[i].smoking_history = smoking_history;

    token = strtok(NULL, ",");
    datos[i].bmi = atof(token);

    token = strtok(NULL, ",");
    datos[i].HbA1c_level = atof(token);

    token = strtok(NULL, ",");
    datos[i].blood_glucose_level = atoi(token);

    token = strtok(NULL, ",");
    datos[i].diabetes = atoi(token);
    token = strtok(NULL, ",");
}

Registro* leer_datos(char* ruta, tipoMinMonticulo* mm) {
    FILE* dataset = abrir_archivo(ruta);

    if (dataset == NULL) {
        printf("\Error. El archivo debe estar abierto.\n");
        exit(-1);
    }
    else {
        Registro* datos = (Registro*)malloc(CANTLINEAS * sizeof(Registro));

        char* linea_leida = leer_linea(dataset);

        int i = 0;
        while (linea_leida != NULL) {
            guardar_registro(linea_leida, datos, i);
            linea_leida = leer_linea(dataset);
            i++;
        }

        cerrar_archivo(dataset);
        return datos;
    }
}