#include <stdbool.h>
#include "registro.h"

typedef struct tipoEl {
	Registro reg;
	float distancia;
} tipoElementoMinMonticulo;

typedef struct tMM {
	tipoElementoMinMonticulo* array;
	int pos;
	int numEl;
} tipoMinMonticulo;

void nuevoMinMonticulo(tipoMinMonticulo*, int);

void insertarMinMonticulo(tipoMinMonticulo*, Registro, float);

void eliminarElementoIndice(tipoMinMonticulo*, int);

void eliminarElemento(tipoMinMonticulo*, tipoElementoMinMonticulo);

tipoElementoMinMonticulo devolverRaiz(tipoMinMonticulo);

void eliminarRaiz(tipoMinMonticulo*);

void mostrarAnchura(tipoMinMonticulo);

bool esVacio(tipoMinMonticulo);

bool estaLleno(tipoMinMonticulo);