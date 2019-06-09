#pragma once
#include "tablero.h"

typedef struct Jugada
{
	int i_pieza;
	int j_pieza;
	int i_destino;
	int j_destino;
} Jugada;

Jugada* jugada_init(int i_pieza, int j_pieza, int i_destino, int j_destino);
void destroy_jugada(Jugada* jugada);
int jugada_valida(Jugada* jugada, Tablero* tablero);
void ejecutar_jugada(Jugada* jugada, Tablero* tablero);
int jugar(Tablero* tablero, int i_pieza, int j_pieza, int i_destino, int j_destino);
