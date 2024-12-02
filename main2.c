#include <stdlib.h>
#include <stdio.h>
#include "lectura_datos.h"
#include "registro.h"
#include "procesamiento_datos.h"

int main() {
    FILE* dataset = abrir_archivo("diabetes_prediction_dataset2.csv");
    Registro reg;
    float total = 0.0, tiene = 0.0, noTiene = 0.0;
    char* linea;

    linea = leer_linea(dataset);
    free(linea);

    while((linea = leer_linea(dataset)) != NULL) {
        total++;
        reg = procesar_linea(linea);
        mostrar_registro(reg);
        printf("\n");

        if (reg.diabetes == 1) {
            tiene += 1;
        } else {
            noTiene += 1;
        }
        free(linea);
    }
    printf("TOTAL: %f\n", total);
    printf("Porcentaje de diabetes: %f\n", (tiene/total)*100);

    cerrar_archivo(dataset);
    return 0;
}