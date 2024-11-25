#include "algoritmo_knn.h"
#include <stdio.h>
#include <stdlib.h>
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
bool algoritmo_knn(tipoMinMonticulo* mm, int k) {
    int contDiabetes = 0, contNoDiabetes = 0, i = 0;
    tipoElementoMinMonticulo* arrayAux = (tipoElementoMinMonticulo*)malloc(k*sizeof(tipoElementoMinMonticulo));

    if (arrayAux == NULL) {
        printf("\nError al reservar memoria\n");
        exit(1);
    }

    tipoElementoMinMonticulo raiz;

    while (!esVacio(*mm) && i < k) {
        raiz = devolverRaiz(*mm);
        (raiz.reg.diabetes ? contDiabetes++ : contNoDiabetes++);
        arrayAux[i] = raiz;
        eliminarElemento(mm, raiz);
        i++;
    }
    
    i = 0;
    while (i < k) {
        insertarMinMonticulo(mm, arrayAux[i].reg, arrayAux[i].distancia);
        i++;
    }
    free(arrayAux);

    if (contDiabetes == contNoDiabetes && !esVacio(*mm)) {
        return (devolverRaiz(*mm).reg.diabetes ? 1 : 0);
    }

    return contDiabetes > contNoDiabetes;
}

void interpretacion_resultado(bool result) {
    printf("\nLa predicción de la clase dice que el sujeto");
    if (!result) printf(" no");
    printf(" tiene diabetes\n");
}

// si el la clase predicha por knn no coincide con la del elemento, este elemento se descarta
void algoritmo_enn(tipoMinMonticulo* mm, int k, tipoMinMonticulo* mm_limpio) {
    int nElem = 100000;
    printf("Registros antes de aplicar ENN: %d\n", nElem);
    int* borrados;
    int nBorrados = 0;
    for (int i = 0; i < 100000; i++) {
        if (algoritmo_knn(mm, k) == mm->array[i].reg.diabetes) {
            float distancia = mm->array[i].distancia;
            Registro reg = mm->array[i].reg;
            insertarMinMonticulo(mm_limpio, reg, distancia);
        } else {
            nBorrados++;
            borrados = (int*)realloc(borrados, nBorrados * sizeof(int));
            borrados[nBorrados-1] = i;
        }
    }
    for (int i = 0; i < nBorrados; i++) {
        eliminarElementoIndice(mm, borrados[i]);
    }

    free(borrados);
    nElem -= nBorrados;
    printf("Registros despues de aplicar ENN: %d\n", nElem);
}
