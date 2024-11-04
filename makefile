PARAMS = -Wall -g

all: moduloLectura main

moduloLectura: lectura_datos.c
	gcc $(PARAMS) -c lectura_datos.c

main: main.c lectura_datos.o
	gcc $(PARAMS) main.c -o main lectura_datos.o