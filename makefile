PARAMS = -Wall -g

FILES = main.c lectura_datos.c algoritmo_knn.c procesamiento_datos.c min_monticulo.c registro.c

COMPILED = main.o lectura_datos.o algoritmo_knn.o procesamiento_datos.o min_monticulo.o registro.o

all: main

main: $(COMPILED)
	gcc $(PARAMS) -o main.o $(COMPILED) -lm

# compilar de .c a .o en base a la call que se haga
%.o: %.c
	gcc $(PARAMS) -c $< -o $@

clean:
	rm -rf *.o