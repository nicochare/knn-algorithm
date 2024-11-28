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
    char* linea_leida;
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
    char* linea_leida;
    int i = 0;
    Registro reg;
    Registro* array = (Registro*)malloc(20*sizeof(Registro));
    tipoCola c2;
    nuevaCola(&c2);

    printf("\nEjemplo de normalización de datos con los primeros 20 registros del dataset.\n");
    
    printf("\nDATOS NO NORMALIZADOS\n");
    while (!esNulaCola(*c)) {
        reg = frente(*c);
        desencolar(c);

        mostrar_registro(reg);
        
        normalizar_registro(&reg);
        array[i] = reg;
        
        encolar(&c2, reg);
        i++;
    }

    printf("\nDATOS NORMALIZADOS\n");
    for (int j = 0; j < i; j++) {
        mostrar_registro(array[j]);
    }

    free(array);
    *c = c2;
}