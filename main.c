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

int main() {
    Registro* conjuntoDeEjemplos = (Registro*)malloc(5*sizeof(Registro));
    
    // TODO: Apartado 1
    tipoCola dataset;
    nuevaCola(&dataset);
    cargar_en_cola(RUTA, &dataset);

    // TODO: Apartado 2
    normalizar_dataset(&dataset);

    // TODO: Apartado 3
    tipoMaxMonticulo mm;
    nuevoMaxMonticulo(&mm, TAMANIODATASET);

    // TODO: Apartado 4
    printf("\n\nClasificación de un ejemplo nuevo mediante K-NN para K=1\n");
    printf("Se utilizará un ejemplo de paciente con los siguientes datos:\n");
    printf("    - Genero:              Hombre\n");
    printf("    - Edad:                37\n");
    printf("    - Hipertension:        No\n");
    printf("    - Enfermedad Cardíaca: No\n");
    printf("    - Historial fumador:   Alguna vez lo fue\n");
    printf("    - BMI:                 25.72\n");
    printf("    - Niveles HbA1c:       3.5\n");
    printf("    - Niveles Glucosa:     149\n\n");
    
    Registro reg_buscado = new_registro(0.0, 37.0, 0.0, 0.0, 6.0, 25.72, 3.5, 149.0);
    normalizar_registro(&reg_buscado);
    cargar_datos(&dataset, &mm, reg_buscado);
    bool resultado = algoritmo_knn(&mm, 1);
    interpretacion_resultado(resultado);

    // TODO: Apartado 5
    printf("\n\nClasificación de un conjunto de ejemplos mediante K-NN para K=1\n");
    
    int i = 0;
    while (i < 5) {
        reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado);
        resultado = algoritmo_knn(&conjuntoDeEjemplos, 1);
        interpretacion_resultado(resultado);
        i++;
    }

    // TODO: Apartado 6
    printf("\n\nClasificación de un ejemplo nuevo mediante K-NN para K=k\n");
    printf("Se utilizará un ejemplo de paciente con los siguientes datos:\n");
    printf("    - Genero:              Hombre\n");
    printf("    - Edad:                37\n");
    printf("    - Hipertension:        No\n");
    printf("    - Enfermedad Cardíaca: No\n");
    printf("    - Historial fumador:   Alguna vez lo fue\n");
    printf("    - BMI:                 25.72\n");
    printf("    - Niveles HbA1c:       3.5\n");
    printf("    - Niveles Glucosa:     149\n\n");
    
    int k = obtener_k();
    
    reg_buscado = new_registro(0.0, 37.0, 0.0, 0.0, 6.0, 25.72, 3.5, 149.0);
    normalizar_registro(&reg_buscado);    
    
    cargar_datos(&dataset, &mm, reg_buscado);
    bool resultado = algoritmo_knn(&mm, k);
    interpretacion_resultado(resultado);

    // TODO: Apartado 7
    printf("\n\nClasificación de un conjunto de ejemplos mediante K-NN para K=k\n");
    
    k = obtener_k();
    
    i = 0;
    while (i < 5) {
        reg_buscado = conjuntoDeEjemplos[i];
        normalizar_registro(&reg_buscado);

        cargar_datos(&dataset, &mm, reg_buscado);
        resultado = algoritmo_knn(&conjuntoDeEjemplos, 1);
        interpretacion_resultado(resultado);
        i++;
    }

    // TODO: Apartado 8
    
    
    return 0;
}