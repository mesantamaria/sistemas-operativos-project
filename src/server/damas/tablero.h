#pragma once

typedef struct Tablero
{
	char ** celdas;
	int turno;
	int start;
} Tablero;

Tablero* tablero_init(int start_player);
void destroy_tablero();
char color(int i, int j);
void tablero_to_char(char* buffer, Tablero* tablero);
int puntaje(Tablero* tablero, int jugador);
int ganador(Tablero* tablero, int jugador);