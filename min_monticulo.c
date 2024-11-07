#include "min_monticulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void nuevoMaxMonticulo(tipoMinMonticulo* mm, int numel) {
	mm->pos = -1;
	mm->numEl = numel;
	mm->array = (tipoElementoMinMonticulo*)malloc(numel * sizeof(tipoElementoMinMonticulo));
}

void swap(tipoMinMonticulo* mm1, int pos1, int pos2) {
	tipoElementoMinMonticulo aux;
	aux = mm1->array[pos1];
	mm1->array[pos1] = mm1->array[pos2];
	mm1->array[pos2] = aux;
}

int padre(int pos) {
	return floor((pos - 1) / 2);
}

int hijoizq(int pos) {
	return pos * 2 + 1;
}

int hijoder(int pos) {
	return pos * 2 + 2;
}

void insertarMaxMonticulo(tipoMinMonticulo* mm, Registro reg, int distancia) {
	if (estaLleno(*mm)) {
		printf("\nError. No se puede añadir elementos a un maxmonticulo lleno.");
	}
	else {
		int auxpos;
		mm->pos += 1;
		auxpos = mm->pos;
		tipoElementoMinMonticulo elem;
		elem.distancia = distancia;
		elem.reg = reg;
		mm->array[auxpos] = elem;

		while (elem.distancia < mm->array[padre(auxpos)].distancia && auxpos > 0) {
			swap(mm, auxpos, padre(auxpos));
			auxpos = padre(auxpos);
		}
	}
}

void eliminarElemento(tipoMinMonticulo* mm, tipoElementoMinMonticulo elem) {
	if (esVacio(*mm)) {
		printf("\nError. No se puede eliminar elementos de un maxmonticulo vacío.");
	}
	else {
		int auxpos, i = 0;
		while (i <= mm->pos && mm->array[i] != elem) {
			i += 1;
		}

		if (mm->array[i] != elem) {
			printf("\nError. El elemento no existe.");
		}
		else {
			auxpos = i;
			mm->array[auxpos] = mm->array[mm->pos];
			mm->pos -= 1;

			while (
				(mm->array[auxpos].distancia < mm->array[hijoizq(auxpos)].distancia ||
					mm->array[auxpos].distancia < mm->array[hijoder(auxpos)].distancia)
				&& hijoder(auxpos) <= mm->pos) {
				if (mm->array[hijoizq(auxpos)].distancia < mm->array[hijoder(auxpos)].distancia) {
					swap(mm, auxpos, hijoder(auxpos));
					auxpos = hijoder(auxpos);
				}
				else {
					swap(mm, auxpos, hijoizq(auxpos));
					auxpos = hijoizq(auxpos);
				}
			}
		}
	}
}

tipoElementoMinMonticulo devolverRaiz(tipoMinMonticulo mm) {
	if (!esVacio(mm)) {
		return (mm.array[0]);
	}
	else {
		printf("\nError. No se puede devolver la raiz de un maxmonticulo vacio.");
		exit(-1);
	}
}

void mostrarAnchura(tipoMinMonticulo mm) {
	for (int i = 0; i <= mm.pos; i++) {
		printf("%d ", mm.array[i].distancia);
	}
}

bool esVacio(tipoMinMonticulo mm) {
	return (mm.pos == -1);
}

bool estaLleno(tipoMinMonticulo mm) {
	return (mm.pos == mm.numEl - 1);
}