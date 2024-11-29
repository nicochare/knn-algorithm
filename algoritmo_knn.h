#ifndef ALGORITMO_KNN_H
#define ALGORITMO_KNN_H
#include "max_monticulo.h"
#include "cola_registros.h"

void interpretacion_resultado(bool);
bool algoritmo_knn(tipoMaxMonticulo*, int);
void algoritmo_enn(tipoCola*, int, tipoMaxMonticulo*);

#endif