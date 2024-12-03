#include "procesamiento_datos.h"
#include "lectura_datos.h"
#include <string.h>
#include <stdlib.h>

void cargar_en_cola(char* ruta, tipoCola* c) {
    FILE* fichero = abrir_archivo(ruta);
    float total = 0.0, tiene = 0.0, noTiene = 0.0;
    char* linea_leida;
    Registro reg;
    
    // Salto primera linea para no leer los nombres de las columnas
    linea_leida = leer_linea(fichero);
    free(linea_leida);

    while ((linea_leida = leer_linea(fichero)) != NULL) {
        total++;
        if (reg.diabetes == 1) {
            tiene += 1;
        } else {
            noTiene += 1;
        }
        reg = procesar_linea(linea_leida);
        encolar(c, reg);
        free(linea_leida);
    }
    desencolar(c);

    printf("Porcentaje de personas con diabetes en el dataset: %.4f%%\n", (tiene/total)*100);
    cerrar_archivo(fichero);
}

void cargar_datos(tipoCola* c, tipoMaxMonticulo* mm, Registro reg_buscado, int k) {
    float distancia = 0;
    int i = 0;
    tipoElementoMaxMonticulo elem;
    Registro reg;
    tipoCola c2;

    nuevaCola(&c2);
    while (!esNulaCola(*c) && i < k) {
        reg = frente(*c);
        desencolar(c);
        encolar(&c2, reg);
        normalizar_registro(&reg);
        distancia = calcular_distancia_registros(reg_buscado, reg);
        insertarMaxMonticulo(mm, reg, distancia);
        i++;
    }

    while (!esNulaCola(*c)) {
        reg = frente(*c);
        desencolar(c);
        encolar(&c2, reg);
        normalizar_registro(&reg);
        distancia = calcular_distancia_registros(reg_buscado, reg);
        if (distancia < devolverRaiz(*mm).distancia) {
            elem.distancia = distancia;
            elem.reg = reg;
            reemplazarRaiz(mm, elem);
        }
    }

    *c = c2;
}

void normalizar_dataset(tipoCola* c) {
    int i = 0; 
    //int nEjemplos = 10;
    Registro reg;
    //Registro* array = (Registro*)malloc(10*sizeof(Registro));
    tipoCola c2;
    nuevaCola(&c2);

    //printf("\nEjemplo de normalización de datos con los primeros %d registros del dataset.\n", nEjemplos);
    
    //printf("\nDATOS NO NORMALIZADOS\n");
    while (!esNulaCola(*c)) {
        reg = frente(*c);
        desencolar(c);

        /*// Solo guardar y mostrar los 10 primeros para mostrar de ejemplo
        if (i < nEjemplos) {
            mostrar_registro(reg);
            normalizar_registro(&reg);
            printf("\n");
            array[i] = reg;
            i++;
        }*/
        
        normalizar_registro(&reg);
        encolar(&c2, reg);
    }

    /*printf("\nDATOS NORMALIZADOS\n");
    for (int j = 0; j < i; j++) {
        mostrar_registro(array[j]);
        printf("\n");
    }

    free(array);*/
    *c = c2;
}

Registro procesar_linea(char* linea_leida) {
    Registro reg;
    char* token = strtok(linea_leida, ",");
    if (token != NULL) {
        if (strcmp(token, "Male") == 0) {
            reg.gender = 0;
        } else {
            reg.gender = 1;
        }
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        reg.age = atof(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        reg.hypertension = atof(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        reg.heart_disease = atof(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        int smoking_history;

        if (strcmp(token, "current") == 0) {
            smoking_history = 1;
        }
        else if (strcmp(token, "former") == 0) {
            smoking_history = 2;
        }
        else if (strcmp(token, "No info") == 0) {
            smoking_history = 3;
        }
        else if (strcmp(token, "never") == 0) {
            smoking_history = 4;
        }
        else if (strcmp(token, "not current") == 0) {
            smoking_history = 5;
        }
        else {
            smoking_history = 6;
        }

        reg.smoking_history = smoking_history;
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        reg.bmi = atof(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        reg.HbA1c_level = atof(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        reg.blood_glucose_level = atof(token);
    }

    token = strtok(NULL, ",");
    if (token != NULL) {
        reg.diabetes = atof(token);
    }

    return reg;
}

void algoritmo_enn(tipoCola* c, int k) {
    int nElem = devolverCantidadElementos(*c);
    int nBorrados = 0;
    Registro reg_buscado;
    tipoMaxMonticulo mm;
    tipoCola c2;

    nuevaCola(&c2);
    nuevoMaxMonticulo(&mm, k);

    printf("N° registros antes de aplicar ENN: %d\n", nElem);
    for (int i = 0; i < nElem; i++) {
        vaciarMaxMonticulo(&mm);
        // Tomo primer elemento, lo borro, hago el MM 
        reg_buscado = frente(*c);
        desencolar(c);
        cargar_datos(c, &mm, reg_buscado, k);
        // y lo vuelvo a agregar (queda al final)
        encolar(c, reg_buscado);
        
        if (algoritmo_knn(&mm, k) != reg_buscado.diabetes) {
            nBorrados++;
        } else {
            encolar(&c2, reg_buscado);
        }
    }
    nElem -= nBorrados;
    printf("N° registros después de aplicar ENN: %d\n", nElem);
    for (int i = 0; i < devolverCantidadElementos(*c); i++) {
        desencolar(c);
    }
    
    *c = c2;
}