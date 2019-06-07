#include <stdlib.h>
#include <stdio.h>
#include "tablero.h"


Tablero* tablero_init() {
	Tablero* t = malloc(sizeof(Tablero));
	t -> celdas = malloc(sizeof(char*) * 8);
	t -> turno = 0;
	int i, j;
	char celda, ficha;
	int negra = 1;
	for (i = 0; i < 8; i++) {
		t -> celdas[i] = malloc(sizeof(char)*8);
		for (j = 0; j < 8; j++) {
			celda = negra ? 'n' : 'b';
			ficha = (i < 3 && ((i % 2 == 0 && j % 2 == 0 || i % 2 == 1 && j % 2 == 1))) ?
				'x' : (i >= 5 && ((i % 2 == 0 && j % 2 == 0 || i % 2 == 1 && j % 2 == 1))) ? 'o' : celda;
			t -> celdas[i][j] = ficha;
			negra = (negra + 1) % 2;
		}
		negra = (negra + 1) % 2;
	}
	return t;
}
void destroy_tablero(Tablero* tablero) {
	int i;
	for (i = 0; i < 8; i++) {
		free(tablero -> celdas[i]);
	}
	free(tablero -> celdas);
	free(tablero);
}