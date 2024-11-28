#include "cola_registros.h"
#include <stdlib.h>
#include <stdio.h>

void nuevaCola(tipoCola* c) {
    c->ini = NULL;
    c->fin = NULL;
    c->cant = 0;
}

bool esNulaCola(tipoCola c) {
    return (c.ini == NULL);
}

void encolar(tipoCola* c, tipoElementoCola e) {
    celdaCola* nuevo;
    c->cant += 1;
    nuevo = (celdaCola*)malloc(sizeof(celdaCola));
    if (nuevo != NULL) {
        nuevo->elem = e; 
        nuevo->sig = NULL;
        if (esNulaCola(*c)) {
            c->ini = nuevo;
            c->fin = nuevo;
        } else if (c->ini->sig == NULL) {
            c->fin = nuevo;
            c->ini->sig = c->fin;
        } else {
            c->fin->sig = nuevo;
            c->fin = nuevo;
        }
    } else {
        printf("\nERROR: Error de asignacion de memoria.\n");
    }
}

void desencolar(tipoCola* c) {
    if (esNulaCola(*c)) {
        printf("\nERROR: No se puede desencolar de cola nula\n");
        exit(-1);
    } else {
        celdaCola* aux;
        c->cant -= 1;
        aux = c->ini;
        c->ini = c->ini->sig;
        free(aux);
    }
}

tipoElementoCola frente(tipoCola c) {
    if (esNulaCola(c)) {
        printf("\nERROR: No se puede llamar a frente en una cola nula\n");
        exit(-1);
    } else {
        return c.ini->elem;
    }
}

int devolverCantidad(tipoCola c) {
    return c.cant;
}