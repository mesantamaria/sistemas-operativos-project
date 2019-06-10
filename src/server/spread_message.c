#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "spread_message.h"

void spread_message(Client* client, Package* message_package){

	char input[255];
	strcpy(input, message_package -> payload);
	// Calculamos el largo del mensaje ingresado por el humano
	int msgLen = calculate_length(input); //no se debería enviar en el payload el caracter nulo al final del input. Ojo que al imprimir el string sin este caracter les aparecerá un simbolo raro al final
	// Armamos el paquete a enviar
	char package[2+msgLen];
	// Definimos el ID, el payloadSize y copiamos el mensaje
	package[0] = 20;
	package[1] = msgLen;
	strcpy(&package[2], input); //debería copiar hasta encontrar un caracter nulo, osea los msgLen caracteres

	// Imprimamos el paquete para ver cómo quedó
	sendMessage(client -> socket, package);

};