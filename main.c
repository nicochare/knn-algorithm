#include "lectura_datos.h"


int main() {
    FILE* dataset = abrirArchivo("diabetes_prediction_dataset.csv");

    Registro* datos = leerDatos(dataset);

    int i = 0;
    printf("GENERO - EDAD - HIPERTENSION - ENFERMEDAD CARDIACA - FUMA - BMI - NIVELES HbA1C - NIVELES GLUCOSA - TIENE DIABETES\n");
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
    cerrarArchivo(dataset);
    return 0;
}