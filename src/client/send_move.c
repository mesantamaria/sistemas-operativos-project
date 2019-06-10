#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "send_move.h"


void send_move(int socket){
	//char package[6];
	char* package = (char*) malloc(7);
	package[0] = 10;
	package[1] = 4;
	char posicion_inicio[2];
	printf("\nIngresa las coordenadas de la pieza a mover (por ejemplo C4): ");
	scanf("%s", posicion_inicio);
	printf("\n");
	char posicion_destino[2];
	printf("\nIngresa las coordenadas de la casilla de destino de la pieza: ");
	scanf("%s", posicion_destino);
	printf("\n");
	strcpy(&package[2], posicion_inicio);
	strcpy(&package[4], posicion_destino);
	sendMessage(socket, package);
	free(package);

}