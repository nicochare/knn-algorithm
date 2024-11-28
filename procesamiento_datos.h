#pragma once
#include "algoritmo_knn.h"
#include "cola_registros.h"

void cargar_datos(tipoCola*, tipoMaxMonticulo*, Registro);

void normalizar_dataset(tipoCola*);

void cargar_en_cola(char*, tipoCola*);