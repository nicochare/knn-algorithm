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

void cerrarArchivo(FILE myFile) {
    fclose(myFile);
}

void guardarRegistro(char* buffer, Registro* datos, int i) {
    char *token = strtok(buffer, ',');
    datos[i].gender = token; 
    token = strtok(NULL, ",");
    datos[i].age = token;
    token = strtok(NULL, ",");
    datos[i].hypertension = token; 
    token = strtok(NULL, ",");
    datos[i].heart_disease = token; 
    token = strtok(NULL, ",");
    datos[i].smoking_history = token; 
    token = strtok(NULL, ",");
    datos[i].bmi = token; 
    token = strtok(NULL, ",");
    datos[i].HbA1c_level = token; 
    token = strtok(NULL, ",");
    datos[i].blood_glucose_level = token; 
    token = strtok(NULL, ",");
    datos[i].diabetes = token; 
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
        
        int i = 0;
        while (fgets(buffer, MAXCARACTERESLINEA, myFile)) {
            guardarRegistro(buffer, datos, i);
            i++;
        }
        return datos;
    }
}