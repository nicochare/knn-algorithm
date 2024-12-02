#include "procesamiento_datos.h"
#include "lectura_datos.h"
#include <string.h>
#include <stdlib.h>

void cargar_en_cola(char* ruta, tipoCola* c) {
    FILE* fichero = abrir_archivo(ruta);
    char* linea_leida;
    Registro reg;

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

Registro procesar_linea(char* linea_leida) {
    Registro reg;
    char* token = strtok(linea_leida, ",");
    if (strcmp(token, "Male") == 0) {
        reg.gender = 0;
    }
    else {
        reg.gender = 1;
    }

    token = strtok(NULL, ",");
    reg.age = atof(token);

    token = strtok(NULL, ",");
    reg.hypertension = atoi(token);

    token = strtok(NULL, ",");
    reg.heart_disease = atoi(token);

    token = strtok(NULL, ",");

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

    token = strtok(NULL, ",");
    reg.bmi = atof(token);

    token = strtok(NULL, ",");
    reg.HbA1c_level = atof(token);

    token = strtok(NULL, ",");
    reg.blood_glucose_level = atoi(token);

    token = strtok(NULL, ",");
    reg.diabetes = atoi(token);
    token = strtok(NULL, ",");
    return reg;
}

// TODO: NECESARIO eliminar el elemento que se este comparando del maxmon y reagregarlo al final
// TODO: NECESARIO ver la forma de mantener el 
//       elemento X en cola hasta el final del analisis y luego borrar ese en especifico.

void algoritmo_enn(tipoCola* c, int k, tipoMaxMonticulo* mm_limpio) {
    int nElem = devolverCantidad(*c);
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
    }

    nElem -= nBorrados;
    printf("N° registros después de aplicar ENN: %d\n", nElem);

    for (int i = 0; i < nElem; i++) {
        desencolar(c);
    }
    
    *c = c2;
}