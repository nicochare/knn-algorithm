#include "lectura_datos.h"
#define MAXCARACTERESLINEA 100
#define CANTLINEAS 100000

FILE abrirArchivo(char *ruta) {
    FILE *myFile = NULL;
    
    myFile = fopen(ruta, "r");
    if (myFile == NULL) {
        printf("\nError de apertura de archivo.\n");
        exit(-1);
    } else {
        return myfile;
    }
}

void guardarRegistro(char* buffer, Registro* datos) {
    char *token = strtok(buffer, ',');
    datos[0].gender = token; 
    token = strtok(NULL, ",");
    datos[0].age = token;
    token = strtok(NULL, ",");
    datos[0].hypertension = token; 
    token = strtok(NULL, ",");
    datos[0].heart_disease = token; 
    token = strtok(NULL, ",");
    datos[0].smoking_history = token; 
    token = strtok(NULL, ",");
    datos[0].bmi = token; 
    token = strtok(NULL, ",");
    datos[0].HbA1c_level = token; 
    token = strtok(NULL, ",");
    datos[0].blood_glucose_level = token; 
    token = strtok(NULL, ",");
    datos[0].diabetes = token; 
    token = strtok(NULL, ",");
}

Registro* leerDatos(FILE myfile) {
    if (myFile == NULL) {
        printf("\Error. El archivo debe estar abierto.\n");
        exit(-1);
    } else {
        Registro* datos = (Registro*)malloc(CANTLINEAS*sizeof(Registro));

        char buffer[MAXCARACTERESLINEA];
        fgets(buffer, MAXCARACTERESLINEA, myFile);

        while (fgets(buffer, MAXCARACTERESLINEA, myFile)) {
            guardarRegistro(buffer, datos);
        }
        return datos;
    }
}


    
