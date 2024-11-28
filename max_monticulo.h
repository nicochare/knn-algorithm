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

void insertarMaxMonticulo(tipoMaxMonticulo *, tipoElementoMaxMonticulo);

void eliminarElemento(tipoMaxMonticulo *, tipoElementoMaxMonticulo);

void eliminarElementoIndice(tipoMaxMonticulo*, int);

tipoElementoMaxMonticulo devolverRaiz(tipoMaxMonticulo);

void mostrarAnchura(tipoMaxMonticulo);

bool esVacio(tipoMaxMonticulo);

bool estaLleno(tipoMaxMonticulo);

void reemplazarRaiz(tipoMaxMonticulo*, tipoElementoMaxMonticulo);