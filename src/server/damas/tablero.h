#pragma once

typedef struct Tablero
{
	char ** celdas;
	int turno;
} Tablero;

Tablero* tablero_init();
void destroy_tablero();
char color(int i, int j);
void tablero_to_char(char* buffer, Tablero* tablero);