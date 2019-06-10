#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "damas/tablero.h"
#include "board_state.h"


void board_state(Client* client, Tablero* tablero){
	char* package = (char*) malloc(67);
	char buffer[64];
    package[0] = 9;
    package[1] = 64;
	tablero_to_char(buffer, tablero);
	printf("%d\n", strlen(buffer));
	strcpy(&package[2], buffer);
	sendMessage(client -> socket, package);
	free(package);
}