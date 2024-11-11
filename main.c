#include "procesamiento_datos.h"
#include "min_monticulo.h"
#include <stdio.h>
#define TAMANIODATASET 100000

int main() {
    tipoMinMonticulo mm;
    nuevoMinMonticulo(&mm, TAMANIODATASET);

    leer_datos("diabetes_prediction_dataset.csv", &mm);

    if (esVacio(mm)) {
        printf("\nError de lectura de datos.\n");
        return 1;
    }
    else {
        int i = 0;
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
        while (!esVacio) {
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