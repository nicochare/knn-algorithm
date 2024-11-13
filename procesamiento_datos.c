#include "lectura_datos.h"
#include "procesamiento_datos.h"
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
    return reg;
}

void mostrar_registro(Registro reg) {
    printf("genero: %d ", reg.gender);
    printf("edad: %f ", reg.age);
    printf("hipertension: %d ", reg.hypertension);
    printf("enfermedad cardíaca: %d ", reg.heart_disease);
    char* smoking_history;
    if (reg.smoking_history == 1) {
        smoking_history = "current";
    }
    else if (reg.smoking_history == 2) {
        smoking_history = "former";
    }
    else if (reg.smoking_history == 3) {
        smoking_history = "No info";
    }
    else if (reg.smoking_history == 4) {
        smoking_history = "never";
    }
    else if (reg.smoking_history == 5) {
        smoking_history = "not current";
    }
    else {
        smoking_history = "ever";
    }
    printf("fumador: %s ", smoking_history);
    printf("IMC: %f ", reg.bmi);
    printf("Niveles HbA1c: %f ", reg.HbA1c_level);
    printf("Niveles glucosa: %d ", reg.blood_glucose_level);
    (reg.diabetes == 1 ? printf("Tiene diabetes: 1 (Si)") : printf("Tiene diabetes: 2 (No)"));
}

void leer_datos(char* ruta, tipoMinMonticulo* mm, Registro reg_buscado) {
    FILE* dataset = abrir_archivo(ruta);

    if (dataset == NULL) {
        printf("\Error. El archivo debe estar abierto.\n");
        exit(-1);
    }
    else {
        char* linea_leida;

        int distancia = 0;
        Registro reg;
        while ((linea_leida = leer_linea(dataset)) != NULL) {
            reg = guardar_registro(linea_leida);
            //tratar_registro(reg_buscado, &reg, &distancia);
            insertarMinMonticulo(mm, reg, distancia);
        }

        cerrar_archivo(dataset);
    }
}