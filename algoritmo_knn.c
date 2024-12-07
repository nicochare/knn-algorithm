#include "algoritmo_knn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool algoritmo_knn(tipoMaxMonticulo* mm, int k, bool diabetes, bool interpretar_resultado) {
    int contDiabetes = 0, contNoDiabetes = 0, i = 0;
    float distancia;
    tipoElementoMaxMonticulo* arrayAux = (tipoElementoMaxMonticulo*)malloc(k * sizeof(tipoElementoMaxMonticulo));

    if (arrayAux == NULL) {
        printf("\nError al reservar memoria\n");
        exit(1);
    }

    tipoElementoMaxMonticulo raiz;

    while (!esVacio(*mm) && i < k) {
        raiz = devolverRaiz(*mm);
        if (raiz.reg.diabetes) {
            contDiabetes++;
        } else {
            contNoDiabetes++;
        }
        arrayAux[i] = raiz;
        eliminarRaiz(mm);
        i++;
    }

    distancia = raiz.distancia;
    
    for (i = 0; i < k; i++) {
        insertarMaxMonticulo(mm, arrayAux[i].reg, arrayAux[i].distancia);
    }


    if (contDiabetes == contNoDiabetes && !esVacio(*mm)) {
        if (devolverRaiz(*mm).reg.diabetes) {
            contDiabetes++;
        } else {
            contNoDiabetes++;
        }
    }

    bool resultado = contDiabetes > contNoDiabetes;

    if (interpretar_resultado) {
        interpretacion_resultado(resultado, raiz.reg.num_registro, raiz.distancia, diabetes == resultado);
    }
    
    free(arrayAux);

    return resultado;
}

void interpretacion_resultado(bool resultado, int num_registro, float distancia, bool exito) {
    printf("\nClosest example: e = %d\n", num_registro);
    printf("Min distance = %.6f\n", distancia);
    printf("Prediction: Class = %d\n", resultado);
    printf("Prediction Success = %d\n", exito);
}