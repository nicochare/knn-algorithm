#include "max_monticulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void nuevoMaxMonticulo(tipoMaxMonticulo* mm, int numel) {
    mm->pos = -1;
    mm->numEl = numel;
    mm->array = (tipoElementoMaxMonticulo*)malloc(numel*sizeof(tipoElementoMaxMonticulo));
}

void swap(tipoMaxMonticulo* mm1, int pos1, int pos2) {
    tipoElementoMaxMonticulo aux;
    aux = mm1->array[pos1];
    mm1->array[pos1] = mm1->array[pos2];
    mm1->array[pos2] = aux;
}

int padre(int pos) {
    return floor((pos-1)/2);
}

int hijoizq(int pos) {
    return pos*2+1;
}

int hijoder(int pos) {
    return pos*2+2;
}

void insertarMaxMonticulo(tipoMaxMonticulo* mm, Registro reg, float distancia) {
    if (estaLleno(*mm)) {
        printf("\nError. No se puede añadir elementos a un maxmonticulo lleno.");
    } else {
        int auxpos;
        tipoElementoMaxMonticulo elem;
        elem.distancia = distancia;
        elem.reg = reg;
        mm->pos += 1;
        auxpos = mm->pos;      
        mm->array[auxpos] = elem;

        while (auxpos > 0 && elem.distancia > mm->array[padre(auxpos)].distancia) {
            swap(mm, auxpos, padre(auxpos));
            auxpos = padre(auxpos);
        }
    }
}

bool compararRegistrosIguales(Registro reg1, Registro reg2) {
	return (reg1.gender == reg2.gender &&
            reg1.age == reg2.age &&
            reg1.hypertension == reg2.hypertension &&
            reg1.heart_disease == reg2.heart_disease &&
            reg1.smoking_history == reg2.smoking_history &&
            reg1.bmi == reg2.bmi &&
            reg1.HbA1c_level == reg2.HbA1c_level &&
            reg1.blood_glucose_level == reg2.blood_glucose_level &&
            reg1.diabetes == reg2.diabetes);
}

bool compararElemsIguales(tipoElementoMaxMonticulo elem, tipoElementoMaxMonticulo elem2) {
    return (elem.distancia == elem2.distancia && compararRegistrosIguales(elem.reg, elem2.reg));
}

void eliminarElementoIndice(tipoMaxMonticulo* mm, int pos) {
	eliminarElemento(mm, mm->array[pos]);
}

void eliminarElemento(tipoMaxMonticulo* mm, tipoElementoMaxMonticulo elem) {
    if (esVacio(*mm)) {
        printf("\nError. No se puede eliminar elementos de un maxmonticulo vacío.");
    } else {
        int auxpos, i = 0;
        while (i <= mm->pos && mm->array[i] != elem) {
            i += 1;
        }

        if (mm->array[i] != elem) {
            printf("\nError. El elemento no existe.");
        } else {
            auxpos = i;
            mm->array[auxpos] = mm->array[mm->pos];
            mm->pos -= 1;

            while (
                (mm->array[auxpos] < mm->array[hijoizq(auxpos)] ||
             mm->array[auxpos] < mm->array[hijoder(auxpos)])
             && hijoder(auxpos) <= mm->pos) {
                if (mm->array[hijoizq(auxpos)] < mm->array[hijoder(auxpos)]) {
                    swap(mm, auxpos, hijoder(auxpos));
                    auxpos = hijoder(auxpos);
                } else {
                    swap(mm, auxpos, hijoizq(auxpos));
                    auxpos = hijoizq(auxpos);
                }
            }
        }
    }
}

void eliminarRaiz(tipoMaxMonticulo* mm) {
	if (esVacio(*mm)) {
		printf("\nError. No se puede eliminar la raiz de un maxmonticulo vacío.\n");
    } else {
		eliminarElemento(mm, mm->array[0]);
    }
}

tipoElementoMaxMonticulo devolverRaiz(tipoMaxMonticulo mm) {
    if (!esVacio(mm)) {
        return (mm.array[0]);
    } else {
        printf("\nError. No se puede devolver la raiz de un maxmonticulo vacio.");
        exit(-1);
    }
}

void mostrarAnchura(tipoMaxMonticulo mm) {
    for (int i = 0; i <= mm.pos; i++) {
        printf("%d ", mm.array[i]);
    }
}

bool esVacio(tipoMaxMonticulo mm) {
    return (mm.pos == -1);
}

bool estaLleno(tipoMaxMonticulo mm) {
    return (mm.pos == mm.numEl-1);
}

int obtenerMayor(tipoMaxMonticulo mm, int pos1, int pos2) {
    return (mm.array[pos1].distancia>mm.array[pos2].distancia ? pos1 : pos2);
}

void reemplazarRaiz(tipoMaxMonticulo* mm, tipoElementoMaxMonticulo elem) {
    mm->array[0] = elem;
    
    int auxpos = 0, mayor = 0;
    while (hijoder(auxpos) <= mm->pos && 
        (mm->array[auxpos].distancia < mm->array[hijoizq(auxpos)].distancia || 
        mm->array[auxpos].distancia < mm->array[hijoder(auxpos)].distancia)) {
            mayor = obtenerMayor(*mm, hijoizq(auxpos), hijoder(auxpos));
            swap(mm, auxpos, mayor);
    }
}

