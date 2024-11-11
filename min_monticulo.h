#include <stdbool.h>
#include "procesamiento_datos.h"

typedef struct tipoEl {
	Registro reg;
	int distancia;
} tipoElementoMinMonticulo;

typedef struct tMM {
	tipoElementoMinMonticulo* array;
	int pos;
	int numEl;
}tipoMinMonticulo;

void nuevoMinMonticulo(tipoMinMonticulo*, int);

void insertarMinMonticulo(tipoMinMonticulo*, Registro, float);

void eliminarElemento(tipoMinMonticulo*, tipoElementoMinMonticulo);

tipoElementoMinMonticulo devolverRaiz(tipoMinMonticulo);

void mostrarAnchura(tipoMinMonticulo);

bool esVacio(tipoMinMonticulo);

bool estaLleno(tipoMinMonticulo);