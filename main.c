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
// TODO: Realizar pruebas con diferentes % de diabéticos, varios dataset, varias k
// TODO: Graficas Python evolucion k y precision con diferentes %
int main() {
    // Apartado 1
    tipoCola dataset;
    nuevaCola(&dataset);
    mostrar_porcentaje(RUTA);
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
    
    tipoCola dataset_ejemplos;
    nuevaCola(&dataset_ejemplos);
    cargar_en_cola("conjunto_knn.csv", &dataset_ejemplos);
    normalizar_dataset(&dataset_ejemplos);

    while (!esNulaCola(dataset_ejemplos)) {
        reg_buscado = frente(dataset_ejemplos);
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado, 1);
        resultado = algoritmo_knn(&mm, 1);
        interpretacion_resultado(resultado);
        desencolar(&dataset_ejemplos);
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
    
    cargar_en_cola("conjunto_knn.csv", &dataset_ejemplos);
    normalizar_dataset(&dataset_ejemplos);

    while (!esNulaCola(dataset_ejemplos)) {
        reg_buscado = frente(dataset_ejemplos);
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado, k);
        resultado = algoritmo_knn(&mm, 1);
        interpretacion_resultado(resultado);
        desencolar(&dataset_ejemplos);
    }

    // Apartado 8
    printf("\n\n\033[33m --- APARTADO 8: Pre-procesamiento del dataset mediante Algoritmo de Wilson (ENN) para K = %d\033[0m\n", k);
    algoritmo_enn(&dataset, k);
    
    

    return 0;
}