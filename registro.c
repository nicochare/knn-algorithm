#include "registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

float normalizar(float v, float max, float min) {
    return ((v - min) / (max - min));
}

void normalizar_registro(Registro* r) {
    r->gender = normalizar(r->gender, 1.0, 0.0);
    r->age = normalizar(r->age, 80.0, 0.08);
    r->hypertension = normalizar(r->hypertension, 1.0, 0.0);
    r->heart_disease = normalizar(r->heart_disease, 1.0, 0.0);
    r->smoking_history = normalizar(r->smoking_history, 6.0, 1.0);
    r->bmi = normalizar(r->bmi, 95.69, 10.01);
    r->HbA1c_level = normalizar(r->HbA1c_level, 9.0, 3.5);
    r->blood_glucose_level = normalizar(r->blood_glucose_level, 300.0, 80.0);
}

float calcular_distancia_registros(Registro r1, Registro r2) {
    return (
        sqrt(pow(r1.gender - r2.gender, 2) + 
             pow(r1.age - r2.age, 2) + 
             pow(r1.hypertension - r2.hypertension, 2) + 
             pow(r1.heart_disease - r2.heart_disease, 2) + 
             pow(r1.smoking_history - r2.smoking_history, 2) + 
             pow(r1.bmi - r2.bmi, 2) + 
             pow(r1.HbA1c_level - r2.HbA1c_level, 2) + 
             pow(r1.blood_glucose_level - r2.blood_glucose_level, 2)
            ));
}

Registro procesar_linea(char* linea_leida) {
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
    printf("genero: %-6.2f ", reg.gender);
    printf("edad: %-6.2f ", reg.age);
    printf("hipertension: %-6.2f ", reg.hypertension);
    printf("enfermedad cardíaca: %-6.2f ", reg.heart_disease);
    printf("fumador: %-6.2f ", reg.smoking_history);
    printf("IMC: %-6.2f ", reg.bmi);
    printf("Niveles HbA1c: %-6.2f ", reg.HbA1c_level);
    printf("Niveles glucosa: %-6.2f ", reg.blood_glucose_level);
    (reg.diabetes == 1 ? printf("Tiene diabetes: 1 (Si) ") : printf("Tiene diabetes: 0 (No) "));
}

void mostrar_registro_distancia(Registro reg, float distancia) {
    printf("genero: %-6.2f ", reg.gender);
    printf("edad: %-6.2f ", reg.age);
    printf("hipertension: %-6.2f ", reg.hypertension);
    printf("enfermedad cardíaca: %-6.2f ", reg.heart_disease);
    printf("fumador: %-6.2f ", reg.smoking_history);
    printf("IMC: %-6.2f ", reg.bmi);
    printf("Niveles HbA1c: %-6.2f ", reg.HbA1c_level);
    printf("Niveles glucosa: %-6.2f ", reg.blood_glucose_level);
    printf("Distancia: %-6.2f ", distancia);
}

Registro obtener_registro_buscado() {
    Registro reg;
    
    printf("Por favor, introduce los datos del registro a analizar:");
    
    do {
        printf("\n    - Genero (0: Hombre, 1: Mujer): ");
        scanf("%f", &reg.gender);
    } while (reg.gender < 0 || reg.gender > 1);
    
    do {
        printf("\n    - Edad: ");
        scanf("%f", &reg.age);
    } while (reg.age < 0);
    
    do {
        printf("\n    - Hipertension (0: No, 1: Si): ");
        scanf("%f", &reg.hypertension);
    } while (reg.hypertension < 0 || reg.hypertension > 1);
    
    do {
        printf("\n    - Enfermedad cardíaca (0: No, 1: Si): ");
        scanf("%f", &reg.heart_disease);
    } while (reg.heart_disease < 0 || reg.heart_disease > 1);
    
    do {        
        printf("\n    - Historial de fumador");
        printf("\n        - 1: Actual");
        printf("\n        - 2: Anterior");
        printf("\n        - 3: Sin información");
        printf("\n        - 4: Nunca");
        printf("\n        - 5: No ahora mismo");
        printf("\n        - 6: Alguna vez lo fue\n    ----> ");
        scanf("%f", &reg.smoking_history);
    } while (reg.smoking_history < 1 || reg.smoking_history > 6);

    do {
        printf("\n    - IMC: ");
        scanf("%f", &reg.bmi);
    } while (reg.bmi < 0);

    printf("\n    - Niveles hemoglobina A1c: ");
    scanf("%f", &reg.HbA1c_level);
    printf("\n    - Niveles glucosa en sangre: ");
    scanf("%f", &reg.blood_glucose_level);

    return reg;
}

Registro new_registro(float gender, float age, float hypertension, float heart_disease, float smoking_history, float bmi, float HbA1c_level, float blood_glucose_level) {
    Registro reg;
    reg.gender = gender;
    reg.age = age;
    reg.hypertension = hypertension;
    reg.heart_disease = heart_disease;
    reg.smoking_history = smoking_history;
    reg.bmi = bmi;
    reg.HbA1c_level = HbA1c_level;
    reg.blood_glucose_level = blood_glucose_level;
    return reg;
}