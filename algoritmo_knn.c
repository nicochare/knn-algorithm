#include "algoritmo_knn.h"
#include "min_monticulo.h"
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

// devuelve la clase predicha por el algoritmo
int algoritmo_knn(tipoMinMonticulo mm, int k) {
    int contDiabetes = 0;
    int contNoDiabetes = 0;
    for (int i = 0; i < k; i++) {
        if (mm.array[i].reg.diabetes = 0) {
            contNoDiabetes++;
        }
        else {
            contDiabetes++;
        }
    }
    // provisional, si es igual, se mira el siguiente
    if (contDiabetes == contNoDiabetes) {
        if (mm.array[k].reg.diabetes = 0) {
            contNoDiabetes++;
        }
        else {
            contDiabetes++;
        }
    }
    if (contDiabetes > contNoDiabetes) { 
        return 1;
    }
    else {
        return 0;
    }
}

// si el la clase predicha por knn no coincide con la del elemento, este elemento se descarta
void algoritmo_enn(tipoMinMonticulo mm, int k, tipoMinMonticulo* mm_limpio) {
    for (int i = 0; i < 100000; i++) {
        if (algoritmo_knn(mm, k) == mm.array[i].reg.diabetes) {
            float distancia = mm.array[i].distancia;
            Registro reg = mm.array[i].reg;
            insertarMinMonticulo(&mm_limpio, reg, distancia);
        }
    }
}