#ifndef COLA_REGISTROS_H
#define COLA_REGISTROS_H
#include <stdbool.h>
#include "registro.h"

typedef Registro tipoElementoCola;

typedef struct celdaC{
	tipoElementoCola elem;
	struct celdaC* sig;
} celdaCola; 

typedef struct tipoC{
	celdaCola* ini;
	celdaCola* fin;
	int cant;
}tipoCola;

void nuevaCola(tipoCola*);

bool esNulaCola(tipoCola);

void encolar(tipoCola*, tipoElementoCola);

void desencolar(tipoCola*);

tipoElementoCola frente(tipoCola);

int devolverCantidadElementos(tipoCola);

#endif