#include "procesamiento_datos.h"
#include "lectura_datos.h"
#include <string.h>
#include <stdlib.h>

float mostrar_porcentaje(char* ruta) {
    FILE* fichero = abrir_archivo(ruta);
    float total = 0.0, tiene = 0.0, noTiene = 0.0;
    char* linea_leida;
    Registro reg;
    
    linea_leida = leer_linea(fichero);
    free(linea_leida);

    while ((linea_leida = leer_linea(fichero)) != NULL) {
        total++;
        reg = procesar_linea(linea_leida, 1);
        if (reg.diabetes == 1) {
            tiene += 1;
        } else {
            noTiene += 1;
        }
        free(linea_leida);
    }

    printf("Porcentaje de personas con diabetes en el dataset: %.4f%%\n", (tiene/total)*100);
    cerrar_archivo(fichero);
}

void cargar_en_cola(char* ruta, tipoCola* c) {
    FILE* fichero = abrir_archivo(ruta);
    int i = 1;
    char* linea_leida;
    Registro reg;
    
    linea_leida = leer_linea(fichero);
    free(linea_leida);

    while ((linea_leida = leer_linea(fichero)) != NULL) {
        reg = procesar_linea(linea_leida, i);
        i++;
        encolar(c, reg);
        free(linea_leida);
    }
    desencolar(c);

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
    Registro reg;
    tipoCola c2;
    nuevaCola(&c2);
    while (!esNulaCola(*c)) {
        reg = frente(*c);
        desencolar(c);
        normalizar_registro(&reg);
        encolar(&c2, reg);
    }
    *c = c2;
}

Registro procesar_linea(char* linea_leida, int i) {
    Registro reg;
    reg.num_registro = i;
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

    for (int i = 0; i < nElem; i++) {
        vaciarMaxMonticulo(&mm);

        reg_buscado = frente(*c);
        desencolar(c);
        cargar_datos(c, &mm, reg_buscado, k);
        encolar(c, reg_buscado);
        
        if (algoritmo_knn(&mm, k, reg_buscado.diabetes, false) != reg_buscado.diabetes) {
            nBorrados++;
        } else {
            encolar(&c2, reg_buscado);
        }
    }
    
    for (int i = 0; i < devolverCantidadElementos(*c); i++) {
        desencolar(c);
    }
    
    *c = c2;
}

void evolucion_acierto(char* RUTA, int k) {
    float aciertos = 0.0;
    tipoCola dataset;
    nuevaCola(&dataset);
    cargar_en_cola(RUTA, &dataset);
    normalizar_dataset(&dataset);

    int nElem = devolverCantidadElementos(dataset);
    Registro reg_buscado;
    tipoMaxMonticulo mm;
    nuevoMaxMonticulo(&mm, k);

    for (int i = 0; i < nElem; i++) {
        vaciarMaxMonticulo(&mm);

        reg_buscado = frente(dataset);
        desencolar(&dataset);
        cargar_datos(&dataset, &mm, reg_buscado, k);
        encolar(&dataset, reg_buscado);
        
        if (algoritmo_knn(&mm, k, true, false) == reg_buscado.diabetes) {
            aciertos++;
        }
    }
    float porcentaje = (float)(aciertos / nElem) * 100.0; 
    printf("PRE-ENN: Accuracy for K=%d = %f\n", k, porcentaje);

    algoritmo_enn(&dataset, k);

    nElem = devolverCantidadElementos(dataset);
    aciertos = 0.0;
    for (int i = 0; i < nElem; i++) {
        vaciarMaxMonticulo(&mm);

        reg_buscado = frente(dataset);
        desencolar(&dataset);
        cargar_datos(&dataset, &mm, reg_buscado, k);
        encolar(&dataset, reg_buscado);
        
        if (algoritmo_knn(&mm, k, true, false) == reg_buscado.diabetes) {
            aciertos++;
        }
    }
    porcentaje = (float)(aciertos / nElem) * 100.0; 
    printf("POST-ENN: Accuracy for K=%d = %f\n\n", k, porcentaje);
}