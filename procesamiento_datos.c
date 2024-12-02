#include "procesamiento_datos.h"
#include "lectura_datos.h"
#include <string.h>
#include <stdlib.h>

void cargar_en_cola(char* ruta, tipoCola* c) {
    FILE* fichero = abrir_archivo(ruta);
    char* linea_leida;
    Registro reg;
    
    // Salto primera linea para no leer los nombres de las columnas
    linea_leida = leer_linea(fichero);
    free(linea_leida);

    while ((linea_leida = leer_linea(fichero)) != NULL) {
        reg = procesar_linea(linea_leida);
        encolar(c, reg);
        free(linea_leida);
    }

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
    Registro* array = (Registro*)malloc(10*sizeof(Registro));
    tipoCola c2;
    nuevaCola(&c2);

    printf("\nEjemplo de normalización de datos con los primeros 20 registros del dataset.\n");
    
    printf("\nDATOS NO NORMALIZADOS\n");
    while (!esNulaCola(*c)) {
        reg = frente(*c);
        desencolar(c);

        // Solo guardar y mostrar los 10 primeros para mostrar de ejemplo
        if (i < 10) {
            mostrar_registro(reg);
            normalizar_registro(&reg);
            printf("\n");
            array[i] = reg;
            i++;
        }
        
        normalizar_registro(&reg);
        encolar(&c2, reg);
    }

    printf("\nDATOS NORMALIZADOS\n");
    for (int j = 0; j < i; j++) {
        mostrar_registro(array[j]);
        printf("\n");
    }

    free(array);
    *c = c2;
}

char* obtener_token(char* linea_leida) {
    char* token = strtok(linea_leida, ",");
    token = strtok(NULL, ",");
    if (token == NULL) {
        return NULL;
    } else {
        return token;

    }
}

Registro procesar_linea(char* linea_leida) {
    Registro reg;
    char* token = strtok(linea_leida, ",");
    if (strcmp(token, "Male") == 0) {
        reg.gender = 0;
    }
    else {
        reg.gender = 1;
    }

    token = obtener_token(linea_leida);
    reg.age = atof(token);

    token = obtener_token(linea_leida);
    reg.hypertension = atoi(token);

    token = obtener_token(linea_leida);
    reg.heart_disease = atoi(token);

    token = obtener_token(linea_leida);

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

    token = obtener_token(linea_leida);
    reg.bmi = atof(token);

    token = obtener_token(linea_leida);
    reg.HbA1c_level = atof(token);

    token = obtener_token(linea_leida);
    reg.blood_glucose_level = atoi(token);

    token = obtener_token(linea_leida);
    reg.diabetes = atoi(token);
    token = obtener_token(linea_leida);
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

    printf("\nN° registros antes de aplicar ENN: %d\n", nElem);
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
        printf("NBORRADOS: %d\n", nBorrados);
    }

    nElem -= nBorrados;
    printf("N° registros después de aplicar ENN: %d\n", nElem);

    for (int i = 0; i < devolverCantidadElementos(*c); i++) {
        desencolar(c);
    }
    
    *c = c2;
}