#ifndef LECTURA_DATOS_H
#define LECTURA_DATOS_H
#include <stdio.h>

FILE* abrir_archivo(char*);

void cerrar_archivo(FILE*);

char* leer_linea(FILE*);

#endif