#include "algoritmo_knn.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool algoritmo_knn(tipoMinMonticulo* mm, int k) {
    int contDiabetes = 0, contNoDiabetes = 0, i = 0;
    tipoElementoMinMonticulo* arrayAux = (tipoElementoMinMonticulo*)malloc(k * sizeof(tipoElementoMinMonticulo));

    if (arrayAux == NULL) {
        printf("\nError al reservar memoria\n");
        exit(1);
    }

    tipoElementoMinMonticulo raiz;

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
        insertarMinMonticulo(mm, arrayAux[i].reg, arrayAux[i].distancia);
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

// TODO: eliminar el elemento que se este comparando del minmonticulo y reagregarlo al final
void algoritmo_enn(tipoMinMonticulo* mm, int k, tipoMinMonticulo* mm_limpio) {
    int nElem = 100000;
    printf("Registros antes de aplicar ENN: %d\n", nElem);
    int* borrados = NULL;
    int nBorrados = 0;
    for (int i = 0; i < 100000; i++) {
        if (algoritmo_knn(mm, k) == mm->array[i].reg.diabetes) {
            float distancia = mm->array[i].distancia;
            Registro reg = mm->array[i].reg;
            insertarMinMonticulo(mm_limpio, reg, distancia);
        } else {
            nBorrados++;
            borrados = (int*)realloc(borrados, nBorrados * sizeof(int));
            borrados[nBorrados - 1] = i;
        }
    }
    for (int i = 0; i < nBorrados; i++) {
        eliminarElementoIndice(mm, borrados[i]);
    }

    free(borrados);
    nElem -= nBorrados;
    printf("Registros despues de aplicar ENN: %d\n", nElem);
}
