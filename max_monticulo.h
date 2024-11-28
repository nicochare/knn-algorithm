#pragma once
#include <stdbool.h>
#include "registro.h"

typedef struct tipoEl {
	Registro reg;
	float distancia;
} tipoElementoMaxMonticulo;

typedef struct tMM {
	tipoElementoMaxMonticulo* array;
	int pos;
	int numEl;
} tipoMaxMonticulo;

void nuevoMaxMonticulo(tipoMaxMonticulo*, int);

void insertarMaxMonticulo(tipoMaxMonticulo *, Registro, float);

void eliminarElemento(tipoMaxMonticulo *, tipoElementoMaxMonticulo);

void eliminarElementoIndice(tipoMaxMonticulo*, int);

void eliminarRaiz(tipoMaxMonticulo*);

tipoElementoMaxMonticulo devolverRaiz(tipoMaxMonticulo);

void mostrarAnchura(tipoMaxMonticulo);

bool esVacio(tipoMaxMonticulo);

bool estaLleno(tipoMaxMonticulo);

void reemplazarRaiz(tipoMaxMonticulo*, tipoElementoMaxMonticulo);