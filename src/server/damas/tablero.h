#pragma once

typedef struct Tablero
{
	char ** celdas;
	int turno;
} Tablero;

Tablero* tablero_init();
void destroy_tablero();