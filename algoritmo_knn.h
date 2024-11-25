#include "min_monticulo.h"

void normalizar_registro(Registro*);
float calcular_distancia_registros(Registro, Registro);
void interpretacion_resultado(bool);
bool algoritmo_knn(tipoMinMonticulo*, int);
void algoritmo_enn(tipoMinMonticulo*, int, tipoMinMonticulo*);