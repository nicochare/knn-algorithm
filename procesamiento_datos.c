#include "procesamiento_datos.h"
#include "lectura_datos.h"
#include "min_monticulo.h"
#include <string.h>
#include <stdlib.h>
#define CANTLINEAS 100000

Registro guardar_registro(char* linea_leida) {
    Registro reg;
    char* token = strtok(linea_leida, ",");
    if (strcmp(token, "Male") == 0) {
        reg.gender = 0;
    }
    else {
        reg.gender = 1;
    }

    token = strtok(NULL, ",");
    reg.age = atof(token);

    token = strtok(NULL, ",");
    reg.hypertension = atoi(token);

    token = strtok(NULL, ",");
    reg.heart_disease = atoi(token);

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

    reg.smoking_history = smoking_history;

    token = strtok(NULL, ",");
    reg.bmi = atof(token);

    token = strtok(NULL, ",");
    reg.HbA1c_level = atof(token);

    token = strtok(NULL, ",");
    reg.blood_glucose_level = atoi(token);

    token = strtok(NULL, ",");
    reg.diabetes = atoi(token);
    token = strtok(NULL, ",");
}

void mostrar_registro(Registro reg) {
 
}

void leer_datos(char* ruta, tipoMinMonticulo* mm, Registro reg_buscado) {
    FILE* dataset = abrir_archivo(ruta);

    if (dataset == NULL) {
        printf("\Error. El archivo debe estar abierto.\n");
        exit(-1);
    }
    else {
        char* linea_leida = leer_linea(dataset);

        int i = 0, distancia = 0;
        Registro reg;
        while (linea_leida != NULL) {
            reg = guardar_registro(linea_leida);
            tratar_registro(reg_buscado, &reg, &distancia);
            insertarMinMonticulo(mm, reg, distancia);
            linea_leida = leer_linea(dataset);
            i++;
        }

        cerrar_archivo(dataset);
    }
}