#include "algoritmo_knn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool algoritmo_knn(tipoMaxMonticulo* mm, int k) {
    int contDiabetes = 0, contNoDiabetes = 0, i = 0;
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

    for (i = 0; i < k; i++) {
        insertarMaxMonticulo(mm, arrayAux[i].reg, arrayAux[i].distancia);
    }
    free(arrayAux);

    if (contDiabetes == contNoDiabetes && !esVacio(*mm)) {
        return devolverRaiz(*mm).reg.diabetes;
    }

    return contDiabetes > contNoDiabetes;
}

void interpretacion_resultado(bool resultado) {
    printf("\nLa predicción de la clase dice que el sujeto");
    if (!resultado) printf(" no");
    printf(" tiene diabetes\n");
}