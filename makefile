PARAMS = -Wall -g

all: moduloLectura moduloProcesamiento main

moduloLectura: lectura_datos.c
	gcc $(PARAMS) -c lectura_datos.c

moduloProcesamiento: procesamiento_datos.c
	gcc $(PARAMS) -c procesamiento_datos.c

main: main.c lectura_datos.o procesamiento_datos.o
	gcc $(PARAMS) main.c -o main lectura_datos.o procesamiento_datos.o