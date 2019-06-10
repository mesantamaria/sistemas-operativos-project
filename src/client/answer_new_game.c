#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "answer_new_game.h"

void answer_new_game(int socket, uint8_t respuesta){

	// Armamos el paquete a enviar
	char package[3];
	// Definimos el ID, el payloadSize y copiamos el mensaje
	package[0] = 16;
	package[1] = 1;
  	package[2] = respuesta;

	// Imprimamos el paquete para ver cómo quedó
	print_package(package);

	sendMessage(socket, package);

}
