usar en linux

1. Introducción de los datos del dataset del problema
2. Normalización de los valores de los atributos numéricos del dataset
3. Creación de la estructura de datos
4. Clasificación de un ejemplo nuevo mediante K-NN para K=1
5. Clasificación de un conjunto de ejemplos para K=1
6. Clasificación de un ejemplo nuevo mediante K-NN para K=k
7. Clasificación de un conjunto de ejemplos para K=k
8. Pre-procesamiento del dataset mediante Algoritmo de Wilson (ENN)
9. Evolución de la precisión de acierto en función del número de ejemplos y la K

###### messi
##### messi
#### messi
### messi
## messi
# messi

void eliminarElemento(tipoMinMonticulo *m, tipoElementoMinMonticulo e) {
    if (esVacio(*m)) {
        printf("ERROR: monticulo vacio\n");
    }
    else {
		int posElem = 0;
		while (posElem < m->pos && m->array[posElem] != e) {
			posElem++;
		}
		if (m->array[posElem] != e) {
			printf("ERROR: elemento no esta en el maxMonticulo\n");
		}
		else {
			m->pos--;
			intercambio(&m->array[posElem], &m->array[m->pos]);
			while((posElem <= m->pos && posElem*2+1 <= m->pos && posElem*2+2 <= m->pos) && (m->array[posElem] > m->array[posElem*2+1] || m->array[posElem] > m->array[posElem*2+2])) {
				if (m->array[posElem*2+1] < m->array[posElem*2+2]) {
					intercambio(&m->array[posElem], &m->array[posElem*2+1]);
					posElem = posElem*2+1;
				}
				else {
					intercambio(&m->array[posElem], &m->array[posElem*2+2]);
					posElem = posElem*2+2;
				}
			}
		}
	}      
}