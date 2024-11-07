#include "procesamiento_datos.h"
#include <stdio.h>

int main() {
    Registro* datos = leer_datos("diabetes_prediction_dataset.csv");

    if (datos == NULL) {
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
        while (i < 10) {
            printf("   %d   - ", datos[i].gender);
            printf("%0.1f - ", datos[i].age);
            printf("%d - ", datos[i].hypertension);
            printf("%d - ", datos[i].heart_disease);
            printf("%d - ", datos[i].smoking_history);
            printf("%f - ", datos[i].bmi);
            printf("%f - ", datos[i].HbA1c_level);
            printf("%d - ", datos[i].blood_glucose_level);
            printf("%d", datos[i].diabetes);
            printf("\n");
            i++;
        }
    }
    return 0;
}