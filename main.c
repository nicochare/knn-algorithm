#include "procesamiento_datos.h"
#include <math.h>
#include <stdio.h>
#define TAMANIODATASET 100000

Registro obtener_registro_buscado() {
    Registro reg;
    
    printf("Por favor, introduce los datos del registro a analizar:");
    
    do {
        printf("\n    - Genero (0: Hombre, 1: Mujer): ");
        scanf("%f", &reg.gender);
    } while (reg.gender < 0 || reg.gender > 1);
    
    do {
        printf("\n    - Edad: ");
        scanf("%f", &reg.age);
    } while (reg.age < 0);
    
    do {
        printf("\n    - Hipertension (0: No, 1: Si): ");
        scanf("%f", &reg.hypertension);
    } while (reg.hypertension < 0 || reg.hypertension > 1);
    
    do {
        printf("\n    - Enfermedad cardíaca (0: No, 1: Si): ");
        scanf("%f", &reg.heart_disease);
    } while (reg.heart_disease < 0 || reg.heart_disease > 1);
    
    do {        
        printf("\n    - Historial de fumador");
        printf("\n        - 1: Actual");
        printf("\n        - 2: Anterior");
        printf("\n        - 3: Sin información");
        printf("\n        - 4: Nunca");
        printf("\n        - 5: No ahora mismo");
        printf("\n        - 6: Alguna vez lo fue\n    ----> ");
        scanf("%f", &reg.smoking_history);
    } while (reg.smoking_history < 1 || reg.smoking_history > 6);

    do {
        printf("\n    - IMC: ");
        scanf("%f", &reg.bmi);
    } while (reg.bmi < 0);

    printf("\n    - Niveles hemoglobina A1c: ");
    scanf("%f", &reg.HbA1c_level);
    printf("\n    - Niveles glucosa en sangre: ");
    scanf("%f", &reg.blood_glucose_level);

    return reg;
}

int obtener_k() {
    int k = 0;
    while (k < 1 || k > TAMANIODATASET) {
        printf("Por favor, introduce la K a utilizar: ");
        scanf("%d", &k);
    }
    return k;
}

int main() {
    tipoMinMonticulo mm;
    nuevoMinMonticulo(&mm, TAMANIODATASET);
    
    char* ruta = "diabetes_prediction_dataset.csv";

    mostrar_normalizacion(ruta);

    Registro reg_buscado = obtener_registro_buscado();
    normalizar_registro(&reg_buscado);

    int k = obtener_k();

    leer_datos(ruta, &mm, reg_buscado);

    if (esVacio(mm)) {
        printf("\nError de lectura de datos.\n");
        return 1;
    } else {
        bool resultado = algoritmo_knn(&mm, k);
        interpretacion_resultado(resultado);
    }

    return 0;
}