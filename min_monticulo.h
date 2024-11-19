#include <stdbool.h>

typedef struct registro {
    float gender; // 0 = Hombre, 1 = Mujer
    float age;
    float hypertension;
    float heart_disease;
    float smoking_history;
    float bmi;
    float HbA1c_level;
    float blood_glucose_level;
    float diabetes; // 0 = No tiene, 1 = Tiene
} Registro;

typedef struct tipoEl {
	Registro reg;
	int distancia;
} tipoElementoMinMonticulo;

typedef struct tMM {
	tipoElementoMinMonticulo* array;
	int pos;
	int numEl;
} tipoMinMonticulo;

void nuevoMinMonticulo(tipoMinMonticulo*, int);

void insertarMinMonticulo(tipoMinMonticulo*, Registro, float);

void eliminarElemento(tipoMinMonticulo*, tipoElementoMinMonticulo);

tipoElementoMinMonticulo devolverRaiz(tipoMinMonticulo);

void mostrarAnchura(tipoMinMonticulo);

bool esVacio(tipoMinMonticulo);

bool estaLleno(tipoMinMonticulo);