#include "algoritmo_knn.h"
#include <math.h>

float distancia_euclidiana(float p, float q) {
    return (sqrt(pow(p - q, 2)));
}

float normalizar(float v, float max, float min) {
    return ((v - min) / (max - min));
}

