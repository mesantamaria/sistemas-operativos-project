#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "estructuras.h"
#include "damas/tablero.h"
#include "damas/utils.h"




int main(int argc, char *argv[])
{
	if (argc < 1)
	{
	    printf("Modo de uso: ./server\n");
	    return 0;
	}

	Tablero* tablero = tablero_init();
	print_tablero(tablero);
	destroy_tablero(tablero);
	return 0;
}
