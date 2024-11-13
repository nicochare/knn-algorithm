#include "procesamiento_datos.h"
#include <stdio.h>
#define TAMANIODATASET 100000

Registro obtener_registro_buscado() {
    Registro reg;
    printf("Por favor, introduce los datos del registro a analizar:");
    do {
        printf("\n    - Genero (0: Hombre, 1: Mujer): ");
        scanf("%d", &reg.gender);
    } while (reg.gender < 0 || reg.gender > 1);
    do {
        printf("\n    - Edad: ");
        scanf("%f", &reg.age);
    } while (reg.age < 0);
    do {
        printf("\n    - Hipertension (0: No, 1: Si): ");
        scanf("%d", &reg.hypertension);
    } while (reg.hypertension < 0 || reg.hypertension > 1);
    do {
        printf("\n    - Enfermedad cardíaca (0: No, 1: Si): ");
        scanf("%d", &reg.heart_disease);
    } while (reg.heart_disease < 0 || reg.heart_disease > 1);
    do
    {        
        printf("\n    - Historial de fumador");
        printf("\n        - 1: Actual");
        printf("\n        - 2: Anterior");
        printf("\n        - 3: Sin información");
        printf("\n        - 4: Nunca");
        printf("\n        - 5: No ahora mismo");
        printf("\n        - 6: Alguna vez lo fue\n    ----> ");
        scanf("%d", &reg.smoking_history);
    } while (reg.smoking_history < 1 || reg.smoking_history > 6);
    do {
        printf("\n    - IMC: ");
        scanf("%f", &reg.bmi);
    } while (reg.bmi < 0);
    printf("\n    - Niveles hemoglobina A1c: ");
    scanf("%f", &reg.HbA1c_level);
    printf("\n    - Niveles glucosa en sangre: ");
    scanf("%d", &reg.blood_glucose_level);

    return reg;
}

int main() {
    tipoMinMonticulo mm;
    nuevoMinMonticulo(&mm, TAMANIODATASET);
    
    char* ruta = "diabetes_prediction_dataset.csv";

    //mostrar_funcionamiento(ruta);
    
    Registro reg_buscado = obtener_registro_buscado();
    leer_datos(ruta, &mm, reg_buscado);

    if (esVacio(mm)) {
        printf("\nError de lectura de datos.\n");
        return 1;
    } else {
        printf("GENERO - ");
        printf("EDAD - ");
        printf("HIPERTENSION - ");
        printf("ENFERMEDAD CARDIACA - ");
        printf("FUMA - ");
        printf("BMI - ");
        printf("NIVELES HbA1C - ");
        printf("NIVELES GLUCOSA - ");
        printf("TIENE DIABETES\n");
        
        tipoElementoMinMonticulo aux;
        while (!esVacio(mm)) {
            aux = devolverRaiz(mm);
            printf("   %d   - ", aux.reg.gender);
            printf("%0.1f - ", aux.reg.age);
            printf("%d - ", aux.reg.hypertension);
            printf("%d - ", aux.reg.heart_disease);
            printf("%d - ", aux.reg.smoking_history);
            printf("%f - ", aux.reg.bmi);
            printf("%f - ", aux.reg.HbA1c_level);
            printf("%d - ", aux.reg.blood_glucose_level);
            printf("%d", aux.reg.diabetes);
            printf("\n");
            eliminarElemento(&mm, devolverRaiz(mm));
        }
    }
    return 0;
}