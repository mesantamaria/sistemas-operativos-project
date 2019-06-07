#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "tablero.h"
#include "utils.h"


void print_tablero(Tablero* tablero) {
	int i, j;
	char* letras = "ABCDEFGH";
	printf("   ");
	for (j = 0; j < 8; j++) {
		printf("| %c ", letras[j]);
	}
	printf("|\n---");
	for (j = 0; j < 8; j++) {
		printf("+---");
	}
	printf("+---\n");
	for (i = 0; i < 8; i++) {
		printf(" %d ", i+1);
		for (j = 0; j < 8; j++) {
			printf("| %c ", to_unicode(tablero -> celdas[i][j]));
		}
		printf("| %d \n---", i+1);
		for (j = 0; j < 8; j++) {
			printf("+---");
		}
		printf("+---\n");
	}
	printf("   ");
	for (j = 0; j < 8; j++) {
		printf("| %c ", letras[j]);
	}
	printf("|\n\n");
}

char to_unicode(char estado) {
	switch(estado) {
		case 'b': return ' ';
		case 'n': return ' ';
		case 'o': return 'o';
		case 'O': return 'O';
		case 'x': return 'x';
		case 'X': return 'X';
		default: return ' ';
	}
}