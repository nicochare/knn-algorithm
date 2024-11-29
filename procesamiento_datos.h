#ifndef PROCESAMIENTO_DATOS_H
#define PROCESAMIENTO_DATOS_H
#include "algoritmo_knn.h"
#include "cola_registros.h"
#include "registro.h"

void cargar_datos(tipoCola*, tipoMaxMonticulo*, Registro, int);

void normalizar_dataset(tipoCola*);

void cargar_en_cola(char*, tipoCola*);

Registro procesar_linea(char*);

void algoritmo_enn(tipoCola*, int, tipoMaxMonticulo*); 

#endif