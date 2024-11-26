#include "procesamiento_datos.h"
#include <math.h>
#include <stdio.h>
#define TAMANIODATASET 100000
#define RUTA "diabetes_prediction_dataset.csv"

int obtener_k() {
    int k = 0;
    while (k < 1 || k > TAMANIODATASET) {
        printf("Por favor, introduce la K a utilizar: ");
        scanf("%d", &k);
    }
    return k;
}

void realizar_apartados(int k) {
    
}

int main() {
    Registro* conjuntoDeEjemplos = (Registro*)malloc(5*sizeof(Registro));
    int k = obtener_k();
    
    // TODO: Apartado 1
    tipoCola dataset;
    nuevaCola(&dataset);
    cargar_en_cola(RUTA, &dataset);

    // TODO: Apartado 2
    normalizar_dataset(&dataset);

    // TODO: Apartado 3
    tipoMinMonticulo mm;
    nuevoMinMonticulo(&mm, TAMANIODATASET);

    // TODO: Apartado 4
    printf("\n\nClasificación de un ejemplo nuevo mediante K-NN para K=1\n");
    
    Registro reg_buscado = new_registro(0.0, 37.0, 0.0, 0.0, 6.0, 25.72, 3.5, 149.0);
    cargar_datos(&dataset, &mm, reg_buscado);
    bool resultado = algoritmo_knn(&mm, 1);
    interpretacion_resultado(resultado);

    // TODO: Apartado 5
    printf("\n\nClasificación de un conjunto de ejemplos mediante K-NN para K=1\n");
    
    int i = 0;
    while (i < 5) {
        Registro reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(RUTA, &mm, reg_buscado);
        resultado = algoritmo_knn(&conjuntoDeEjemplos, 1);
        interpretacion_resultado(resultado);
        i++;
    }

    printf("\n\nClasificación de un ejemplo nuevo mediante K-NN para K=k\n");
    bool resultado = algoritmo_knn(mm, k);
    interpretacion_resultado(resultado);

    printf("\n\nClasificación de un conjunto de ejemplos mediante K-NN para K=k\n");
    while (!esVacio(conjuntoDeEjemplos)) {
        Registro reg_buscado = cima(conjuntoDeEjemplos);
        normalizar_registro(&reg_buscado);

        cargar_datos(RUTA, &mm, reg_buscado);
        resultado = algoritmo_knn(&conjuntoDeEjemplos, k);
        interpretacion_resultado(resultado);
    }
    
    return 0;
}