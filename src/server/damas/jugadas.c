#include <stdlib.h>
#include <stdio.h>
#include "jugadas.h"
#include "tablero.h"
#include "utils.h"

Jugada* jugada_init(int i_pieza, int j_pieza, int i_destino, int j_destino) {
	Jugada* jugada = malloc(sizeof(Jugada));
	jugada -> i_pieza = i_pieza;
	jugada -> j_pieza = j_pieza;
	jugada -> i_destino = i_destino;
	jugada -> j_destino = j_destino;
	return jugada;
}

void destroy_jugada(Jugada* jugada) {
	free(jugada);
}

int jugada_valida(Jugada* jugada, Tablero* tablero) {
	int i_pieza = jugada -> i_pieza;
	int j_pieza = jugada -> j_pieza;
	int i_destino = jugada -> i_destino;
	int j_destino = jugada -> j_destino;
	char actual = tablero -> turno ? 'x' : 'o';
	char enemigo = tablero -> turno ? 'o' : 'x';
	// La ficha elegida debe ser del jugador actual
	char ficha = tablero -> celdas[i_pieza][j_pieza];
	if (ficha != actual) {
		printf("Jugada no valida: Solo puedes mover tus fichas.\n");
		return 0;
	}
	// La celda de destino debe estar vacia
	char destino = tablero -> celdas[i_destino][j_destino];
	if (destino != 'b' && destino != 'n') {
		printf("Jugada no valida: Debes elegir una celda de destino vacia.\n");
		return 0;
	}
	int delta_i = i_destino - i_pieza;
	int delta_j = j_destino - j_pieza;
	// Debe moverse la misma cantidad de espacios en ambos ejes
	if (abs(delta_i) != abs(delta_j)) {
		printf("Jugada no valida: Solo puedes moverte en diagonal.\n");
		return 0;
	}
	// Debe moverse a lo más dos espacios en diagonal (avanzar o comerse a otra pieza)
	if (abs(delta_i) > 2) {
		printf("Jugada no valida: No puedes avanzar más de dos espacios.\n");
		return 0;
	}
	// Debe moverse por lo menos un espacio
	if (abs(delta_i) < 1) {
		printf("Jugada no valida: No puedes quedarte en el mismo lugar.\n");
		return 0;
	}
	// Solo se puede avanzar hacia adelante
	if (actual == 'o' && delta_i > 0 || actual == 'x' && delta_i < 0) {
		return 0;
	}
	// Si se mueve dos, debe haber una ficha enemiga entremedio
	// TODO: El resto de las movidas posibles (comidas en cadena)
	if (abs(delta_i) >= 2 && abs(delta_i) % 2 == 0){
		char entremedio = tablero -> celdas[i_pieza + delta_i / 2][j_pieza + delta_j / 2];
		if (entremedio != enemigo) {
			printf("Jugada no valida: Debes comerte una ficha enemiga para hacer eso.");
			return 0;
		}
	}
	return 1;
}

// Asume que la jugada es válida
void ejecutar_jugada(Jugada* jugada, Tablero* tablero) {
	int i_pieza = jugada -> i_pieza;
	int j_pieza = jugada -> j_pieza;
	int i_destino = jugada -> i_destino;
	int j_destino = jugada -> j_destino;
	int pieza = tablero -> celdas[i_pieza][j_pieza];
	// Sacamos la pieza de su ubicación
	tablero -> celdas[i_pieza][j_pieza] = color(i_pieza, j_pieza);
	// Ponemos la pieza en su nueva posición
	tablero -> celdas[i_destino][j_destino] = pieza;

	int delta_i = i_destino - i_pieza;
	int delta_j = j_destino - j_pieza;
	// Si se movio 2 espacios, comerse a la pieza de entremedio.
	if (abs(delta_i) == 2) {
		tablero -> celdas[i_pieza + delta_i / 2][j_pieza + delta_j / 2] = color(i_pieza + delta_i / 2, j_pieza + delta_j / 2);
	}
	else {
		tablero -> turno = (tablero -> turno + 1) % 2;
	}
}

int jugar(Tablero* tablero, int i_pieza, int j_pieza, int i_destino, int j_destino) {
	// i = fila, j = columna
	Jugada* jugada = jugada_init(i_pieza, j_pieza, i_destino, j_destino);
	if (jugada_valida(jugada, tablero)) {
		ejecutar_jugada(jugada, tablero);
		destroy_jugada(jugada);
		print_tablero(tablero);
		return 1;
	}
	else {
		destroy_jugada(jugada);
		//print_tablero(tablero);
		return 0;
	}
}