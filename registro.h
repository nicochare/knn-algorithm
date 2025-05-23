#ifndef REGISTRO_H
#define REGISTRO_H

typedef struct registro {
    int num_registro;
    float gender; 
    float age;
    float hypertension;
    float heart_disease;
    float smoking_history;
    float bmi;
    float HbA1c_level;
    float blood_glucose_level;
    float diabetes; 
} Registro;

float normalizar(float, float, float);

void normalizar_registro(Registro*);

float calcular_distancia_registros(Registro, Registro);

void mostrar_registro(Registro);

void mostrar_registro_distancia(Registro, float);

Registro obtener_registro_buscado();

Registro nuevo_registro(int, float, float, float, float, float, float, float, float);

#endif