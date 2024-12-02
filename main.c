#include "procesamiento_datos.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define RUTA "diabetes_prediction_dataset2.csv"

int obtener_k(int max) {
    int k = 0;
    while (k < 1) {
        printf("(1 <= k <= %d)\n", max);
        printf("\nPor favor, introduce el numero de registros con los que desea comparar (k): ");
        scanf("%d", &k);
    }
    return k;
}

int main() {
    // Apartado 1
    tipoCola dataset;
    nuevaCola(&dataset);
    cargar_en_cola(RUTA, &dataset);

    int k = obtener_k(devolverCantidadElementos(dataset));

    // Apartado 2
    normalizar_dataset(&dataset);

    // Apartado 3
    tipoMaxMonticulo mm;
    nuevoMaxMonticulo(&mm, devolverCantidadElementos(dataset));

    // Apartado 4
    printf("\n\n\033[33m --- APARTADO 4: Clasificación de un ejemplo nuevo mediante K-NN para K=1\033[0m\n");
    printf("Se utilizará un ejemplo de paciente con los siguientes datos:\n");
    printf("    - Genero:              Hombre\n");
    printf("    - Edad:                81\n");
    printf("    - Hipertension:        Si\n");
    printf("    - Enfermedad Cardíaca: Si\n");
    printf("    - Historial fumador:   Actualmente no\n");
    printf("    - BMI:                 26.92\n");
    printf("    - Niveles HbA1c:       7.4\n");
    printf("    - Niveles Glucosa:     162\n\n");
    
    Registro reg_buscado = nuevo_registro(0.0, 81.0, 1.0, 1.0, 5.0, 26.92, 7.4, 162.0); // diabetes
    normalizar_registro(&reg_buscado);
    cargar_datos(&dataset, &mm, reg_buscado, 1);
    bool resultado = algoritmo_knn(&mm, 1);
    interpretacion_resultado(resultado);

    // Apartado 5
    printf("\n\n\033[33m --- APARTADO 5: Clasificación de un conjunto de ejemplos mediante K-NN para K=1\033[0m\n");
    
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
    printf("\n\n\033[33m --- APARTADO 6: Clasificación de un ejemplo nuevo mediante K-NN para K=k\033[0m\n");
    printf("Se utilizará un ejemplo de paciente con los siguientes datos:\n");
    printf("    - Genero:              Hombre\n");
    printf("    - Edad:                81\n");
    printf("    - Hipertension:        Si\n");
    printf("    - Enfermedad Cardíaca: Si\n");
    printf("    - Historial fumador:   Actualmente no\n");
    printf("    - BMI:                 26.92\n");
    printf("    - Niveles HbA1c:       7.4\n");
    printf("    - Niveles Glucosa:     162\n\n");
    
    reg_buscado = nuevo_registro(0.0, 81.0, 1.0, 1.0, 5.0, 26.92, 7.4, 162.0); // diabetes
    normalizar_registro(&reg_buscado);    
    
    cargar_datos(&dataset, &mm, reg_buscado, k);
    resultado = algoritmo_knn(&mm, k);
    interpretacion_resultado(resultado);

    // Apartado 7
    printf("\n\n\033[33m --- APARTADO 7: Clasificación de un conjunto de ejemplos mediante K-NN para K=k\033[0m\n");
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
    printf("\n\n\033[33m --- APARTADO 8: Pre-procesamiento del dataset mediante Algoritmo de Wilson (ENN) para K = %d\033[0m\n", k);
    algoritmo_enn(&dataset, k);
    
    printf("REPETICION APARTADOS 6 y 7\n");
    // Apartado 4
    printf("\n\n\033[33m --- APARTADO 4: Clasificación de un ejemplo nuevo mediante K-NN para K=1\033[0m\n");
    printf("Se utilizará un ejemplo de paciente con los siguientes datos:\n");
    printf("    - Genero:              Hombre\n");
    printf("    - Edad:                81\n");
    printf("    - Hipertension:        Si\n");
    printf("    - Enfermedad Cardíaca: Si\n");
    printf("    - Historial fumador:   Actualmente no\n");
    printf("    - BMI:                 26.92\n");
    printf("    - Niveles HbA1c:       7.4\n");
    printf("    - Niveles Glucosa:     162\n\n");
    
    reg_buscado = nuevo_registro(0.0, 81.0, 1.0, 1.0, 5.0, 26.92, 7.4, 162.0); // diabetes
    normalizar_registro(&reg_buscado);
    cargar_datos(&dataset, &mm, reg_buscado, 1);
    resultado = algoritmo_knn(&mm, 1);
    interpretacion_resultado(resultado);

    // Apartado 5
    printf("\n\n\033[33m --- APARTADO 5: Clasificación de un conjunto de ejemplos mediante K-NN para K=1\033[0m\n");
    
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

    printf("\n\nClasificación de un ejemplo nuevo mediante K-NN para K=k\n");
    printf("Se utilizará un ejemplo de paciente con los siguientes datos:\n");
    printf("    - Genero:              Hombre\n");
    printf("    - Edad:                81\n");
    printf("    - Hipertension:        Si\n");
    printf("    - Enfermedad Cardíaca: Si\n");
    printf("    - Historial fumador:   Actualmente no\n");
    printf("    - BMI:                 26.92\n");
    printf("    - Niveles HbA1c:       7.4\n");
    printf("    - Niveles Glucosa:     162\n\n");
    
    k = obtener_k(devolverCantidadElementos(dataset));
    
    reg_buscado = nuevo_registro(0.0, 81.0, 1.0, 1.0, 5.0, 26.92, 7.4, 162.0); // diabetes
    normalizar_registro(&reg_buscado);    
    
    cargar_datos(&dataset, &mm, reg_buscado, k);
    resultado = algoritmo_knn(&mm, k);
    interpretacion_resultado(resultado);

    // Apartado 7
    printf("\n\nClasificación de un conjunto de ejemplos mediante K-NN para K=k\n");
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

    // 

    return 0;
}