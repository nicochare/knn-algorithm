#include <stdio.h>
#include <stdlib.h>
#include "procesamiento_datos.h"

void pruebaCompleta(char* RUTA, int k) {
    // Apartado 1
    tipoCola dataset;
    nuevaCola(&dataset);
    cargar_en_cola(RUTA, &dataset);

    // Apartado 2
    normalizar_dataset(&dataset);

    // Apartado 3
    tipoMaxMonticulo mm;
    nuevoMaxMonticulo(&mm, devolverCantidadElementos(dataset));

    // Apartado 4
    printf("\n\033[33m --- Clasificación de un ejemplo nuevo mediante K-NN para K=1\033[0m\n");
    Registro reg_buscado = nuevo_registro(0.0, 81.0, 1.0, 1.0, 5.0, 26.92, 7.4, 162.0); // diabetes
    normalizar_registro(&reg_buscado);
    cargar_datos(&dataset, &mm, reg_buscado, 1);
    bool resultado = algoritmo_knn(&mm, 1);
    interpretacion_resultado(resultado);

    // Apartado 5
    printf("\n\033[33m --- Clasificación de un conjunto de ejemplos mediante K-NN para K=1\033[0m\n");
    Registro* conjuntoDeEjemplos = (Registro*)malloc(5*sizeof(Registro));
    conjuntoDeEjemplos[0] = nuevo_registro(0.0, 64.0, 0.0, 0.0, 5.0, 31.7, 6.2, 162.0); // no diabetes
    conjuntoDeEjemplos[1] = nuevo_registro(1.0, 36.0, 0.0, 0.0, 3.0, 55.91, 7.0, 151.0); // diabetes
    conjuntoDeEjemplos[2] = nuevo_registro(0.0, 39.0, 0.0, 0.0, 3.0, 27.98, 5.9, 284.0); // diabetes
    conjuntoDeEjemplos[3] = nuevo_registro(1.0, 53.0, 0.0, 0.0, 4.0, 26.81, 6.7, 158.0); // no diabetes
    conjuntoDeEjemplos[4] = nuevo_registro(1.0, 10.0, 0.0, 0.0, 3.0, 28.86, 6.1, 93.0); // no diabetes

    int i = 0;
    while (i < 5) {
        reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado, 1);
        resultado = algoritmo_knn(&mm, 1);
        interpretacion_resultado(resultado);
        i++;
    }

    // Apartado 6
    printf("\n\033[33m --- Clasificación de un ejemplo nuevo mediante K-NN para K=%d\033[0m\n", k);
    reg_buscado = nuevo_registro(0.0, 81.0, 1.0, 1.0, 5.0, 26.92, 7.4, 162.0); // diabetes
    normalizar_registro(&reg_buscado);    
    cargar_datos(&dataset, &mm, reg_buscado, k);
    resultado = algoritmo_knn(&mm, k);
    interpretacion_resultado(resultado);

    // Apartado 7
    printf("\n\033[33m --- Clasificación de un conjunto de ejemplos mediante K-NN para K=%d\033[0m\n", k);
    conjuntoDeEjemplos[0] = nuevo_registro(0.0, 64.0, 0.0, 0.0, 5.0, 31.7, 6.2, 162.0); // no diabetes
    conjuntoDeEjemplos[1] = nuevo_registro(1.0, 36.0, 0.0, 0.0, 3.0, 55.91, 7.0, 151.0); // diabetes
    conjuntoDeEjemplos[2] = nuevo_registro(0.0, 39.0, 0.0, 0.0, 3.0, 27.98, 5.9, 284.0); // diabetes
    conjuntoDeEjemplos[3] = nuevo_registro(1.0, 53.0, 0.0, 0.0, 4.0, 26.81, 6.7, 158.0); // no diabetes
    conjuntoDeEjemplos[4] = nuevo_registro(1.0, 10.0, 0.0, 0.0, 3.0, 28.86, 6.1, 93.0); // no diabetes

    i = 0;
    while (i < 5) {
        reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado, k);
        resultado = algoritmo_knn(&mm, k);
        interpretacion_resultado(resultado);
        i++;
    }

    // Apartado 8
    printf("\n\033[33m --- Pre-procesamiento del dataset mediante Algoritmo de Wilson (ENN) para K=%d\033[0m\n", k);
    algoritmo_enn(&dataset, k);

    // Apartado 4
    printf("\n\033[33m --- (Despues de ENN) Clasificación de un ejemplo nuevo mediante K-NN para K=1\033[0m\n");
    reg_buscado = nuevo_registro(0.0, 81.0, 1.0, 1.0, 5.0, 26.92, 7.4, 162.0); // diabetes
    normalizar_registro(&reg_buscado);
    cargar_datos(&dataset, &mm, reg_buscado, 1);
    resultado = algoritmo_knn(&mm, 1);
    interpretacion_resultado(resultado);

    // Apartado 5
    printf("\n\033[33m --- (Despues de ENN) Clasificación de un conjunto de ejemplos mediante K-NN para K=1\033[0m\n");
    conjuntoDeEjemplos = (Registro*)malloc(5*sizeof(Registro));
    conjuntoDeEjemplos[0] = nuevo_registro(0.0, 64.0, 0.0, 0.0, 5.0, 31.7, 6.2, 162.0); // no diabetes
    conjuntoDeEjemplos[1] = nuevo_registro(1.0, 36.0, 0.0, 0.0, 3.0, 55.91, 7.0, 151.0); // diabetes
    conjuntoDeEjemplos[2] = nuevo_registro(0.0, 39.0, 0.0, 0.0, 3.0, 27.98, 5.9, 284.0); // diabetes
    conjuntoDeEjemplos[3] = nuevo_registro(1.0, 53.0, 0.0, 0.0, 4.0, 26.81, 6.7, 158.0); // no diabetes
    conjuntoDeEjemplos[4] = nuevo_registro(1.0, 10.0, 0.0, 0.0, 3.0, 28.86, 6.1, 93.0); // no diabetes

    i = 0;
    while (i < 5) {
        reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado, 1);
        resultado = algoritmo_knn(&mm, 1);
        interpretacion_resultado(resultado);
        i++;
    }

    // Apartado 6
    printf("\n\033[33m --- (Despues de ENN) Clasificación de un ejemplo nuevo mediante K-NN para K=%d\033[0m\n", k);
    reg_buscado = nuevo_registro(0.0, 81.0, 1.0, 1.0, 5.0, 26.92, 7.4, 162.0); // diabetes
    normalizar_registro(&reg_buscado);    
    cargar_datos(&dataset, &mm, reg_buscado, k);
    resultado = algoritmo_knn(&mm, k);
    interpretacion_resultado(resultado);

    // Apartado 7
    printf("\n\033[33m --- (Despues de ENN) Clasificación de un conjunto de ejemplos mediante K-NN para K=%d\033[0m\n", k);
    conjuntoDeEjemplos[0] = nuevo_registro(0.0, 64.0, 0.0, 0.0, 5.0, 31.7, 6.2, 162.0); // no diabetes
    conjuntoDeEjemplos[1] = nuevo_registro(1.0, 36.0, 0.0, 0.0, 3.0, 55.91, 7.0, 151.0); // diabetes
    conjuntoDeEjemplos[2] = nuevo_registro(0.0, 39.0, 0.0, 0.0, 3.0, 27.98, 5.9, 284.0); // diabetes
    conjuntoDeEjemplos[3] = nuevo_registro(1.0, 53.0, 0.0, 0.0, 4.0, 26.81, 6.7, 158.0); // no diabetes
    conjuntoDeEjemplos[4] = nuevo_registro(1.0, 10.0, 0.0, 0.0, 3.0, 28.86, 6.1, 93.0); // no diabetes

    i = 0;
    while (i < 5) {
        reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado, k);
        resultado = algoritmo_knn(&mm, k);
        interpretacion_resultado(resultado);
        i++;
    }
}

int main() {
    char* rutas[11] = {"diabetes_prediction_dataset2.csv", "diabetes_subset_50_50.csv", "filtered_diabetes_subset_50_50.csv", 
                    "diabetes_subset_55_45.csv", "filtered_diabetes_subset_55_45.csv", "diabetes_subset_60_40.csv", 
                    "filtered_diabetes_subset_60_40.csv", "diabetes_subset_65_35.csv", "filtered_diabetes_subset_65_35.csv", 
                    "diabetes_subset_70_30.csv", "filtered_diabetes_subset_70_30.csv"};
    int valores_k[14] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 14; j++) {
            printf("\n\n--- RUTA: %s, K: %d ---\n\n", rutas[i], valores_k[j]);
            pruebaCompleta(rutas[i], valores_k[j]);
        }
    }

    return 0;
}