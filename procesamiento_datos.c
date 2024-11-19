#include "procesamiento_datos.h"
#include "lectura_datos.h"
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
    printf("genero: %0.2f ", reg.gender);
    printf("edad: %0.2f ", reg.age);
    printf("hipertension: %0.2f ", reg.hypertension);
    printf("enfermedad cardíaca: %0.2f ", reg.heart_disease);
    printf("fumador: %0.2f ", reg.smoking_history);
    printf("IMC: %0.2f ", reg.bmi);
    printf("Niveles HbA1c: %0.2f ", reg.HbA1c_level);
    printf("Niveles glucosa: %0.2f ", reg.blood_glucose_level);
    (reg.diabetes == 1 ? printf("Tiene diabetes: 1 (Si)") : printf("Tiene diabetes: 0 (No)"));
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
        leer_linea(dataset); // Nombres de columnas
        while ((linea_leida = leer_linea(dataset)) != NULL) {
            reg = guardar_registro(linea_leida);
            //tratar_registro(reg_buscado, &reg, &distancia);
            insertarMinMonticulo(mm, reg, distancia);
        }

        cerrar_archivo(dataset);
    }
}

void mostrar_normalizacion(char* ruta) {
    FILE* dataset = abrir_archivo(ruta);

    if (dataset == NULL) {
        printf("\nError. El archivo debe estar abierto.\n");
        exit(-1);
    } else {
        printf("\nEjemplo de normalización de datos con los primeros 20 registros del dataset.\n");
        char* linea_leida;
        int i = 0;
        Registro reg;
        Registro* array = (Registro*)malloc(20*sizeof(Registro));
        
        // Salto primera linea (columnas)
        linea_leida = leer_linea(dataset);

        while ((linea_leida = leer_linea(dataset)) != NULL && i < 20) {
            reg = guardar_registro(linea_leida);
            array[i] = reg;
            free(linea_leida);
            i++;
        }
        printf("DATOS SIN NORMALIZAR:\n");
        for (int j = 0; j < i; j++) {
            mostrar_registro(array[j]);
            printf("\n");
        }
        printf("DATOS NORMALIZADOS:\n");
        for (int j = 0; j < i; j++) {
            normalizar_registro(&array[j]);
            mostrar_registro(array[j]);
            printf("\n");
        }

        free(array);
        cerrar_archivo(dataset);
    }
}