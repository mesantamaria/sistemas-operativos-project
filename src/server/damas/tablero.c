#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tablero.h"


Tablero* tablero_init(int start_player) {
	Tablero* t = malloc(sizeof(Tablero));
	t -> celdas = malloc(sizeof(char*) * 8);
	t -> turno = start_player;
	int i, j;
	char celda, ficha;
	int negra = 1;
	for (i = 0; i < 8; i++) {
		t -> celdas[i] = malloc(sizeof(char) * 9);
		for (j = 0; j < 8; j++) {
			celda = negra ? 'n' : 'b';
			ficha = i < 3 && color(i, j) == 'n' ?
				'x' : i >= 5 && color(i, j) == 'n' ?
				'o' : celda;
			t -> celdas[i][j] = ficha;
			negra = (negra + 1) % 2;
		}
		t -> celdas[i][8] = '\x0';
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

char color(int i, int j) {
	return i % 2 == 0 && j % 2 == 0 || i % 2 == 1 && j % 2 == 1 ? 'n' : 'b';
}

void tablero_to_char(char* buffer, Tablero* tablero) {
	int i;
	strcpy(buffer, tablero -> celdas[0]);
	for (i = 1; i < 8; i++) {
		strcat(buffer, tablero -> celdas[i]);
	}
}

int puntaje(Tablero* tablero, int jugador) {
	int puntaje = 12;
	// Se cuentan los del enemigo asi que se ve al reves
	char ficha = jugador ? 'o' : 'x';
	char dama = jugador ? 'O' : 'X';
	char celda;
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			celda = tablero -> celdas[i][j];
			if (celda == ficha || celda == dama) {
				puntaje--;
			}
		}
	}
	return puntaje;
}

int ganador(Tablero* tablero, int jugador) {
	if (puntaje(tablero, jugador) == 12) {
		return 1;
	}
	else {
		return 0;
	}
}