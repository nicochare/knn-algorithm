# Warnings y debugging
PARAMS = -Wall -g

all: main

modulo_algoritmo: algoritmo_knn.c
	gcc $(PARAMS) -c algoritmo_knn.c

modulo_lectura: lectura_datos.c
	gcc $(PARAMS) -c lectura_datos.c

modulo_procesamiento: procesamiento_datos.c
	gcc $(PARAMS) -c procesamiento_datos.c

modulo_maxmonticulo: max_monticulo.c
	gcc $(PARAMS) -c max_monticulo.c

modulo_registro: registro.c
	gcc $(PARAMS) -c registro.c

modulo_cola: cola_registros.c
	gcc $(PARAMS) -c cola_registros.c

main: main.c lectura_datos.o algoritmo_knn.o procesamiento_datos.o max_monticulo.o registro.o cola_registros.o
	gcc $(PARAMS) main.c -o main.o algoritmo_knn.o lectura_datos.o procesamiento_datos.o max_monticulo.o cola_registros.o registro.o -lm

# TODO: Borrar esto
main2:
	gcc $(PARAMS) main2.c -o main2.o algoritmo_knn.o lectura_datos.o procesamiento_datos.o max_monticulo.o cola_registros.o registro.o -lm
clean:
	rm -rf *.o