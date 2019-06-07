#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "opponent_found.h"

void opponent_found(Client** clients){

	char* input = clients[1] -> nickname;
	// Calculamos el largo del mensaje ingresado por el humano
	int msgLen = calculate_length(input); //no se debería enviar en el payload el caracter nulo al final del input. Ojo que al imprimir el string sin este caracter les aparecerá un simbolo raro al final
	// Armamos el paquete a enviar
	char package[2+msgLen];
	// Definimos el ID, el payloadSize y copiamos el mensaje
	package[0] = 5;
	package[1] = msgLen;
	strcpy(&package[2], input); //debería copiar hasta encontrar un caracter nulo, osea los msgLen caracteres

	// Imprimamos el paquete para ver cómo quedó
	sendMessage(clients[0] -> socket, package);


	char* input2 = clients[0] -> nickname;
	// Calculamos el largo del mensaje ingresado por el humano
	int msgLen2 = calculate_length(input2); //no se debería enviar en el payload el caracter nulo al final del input. Ojo que al imprimir el string sin este caracter les aparecerá un simbolo raro al final
	// Armamos el paquete a enviar
	char package1[2+msgLen2];
	// Definimos el ID, el payloadSize y copiamos el mensaje
	package1[0] = 5;
	package1[1] = msgLen2;
	strcpy(&package1[2], input2); //debería copiar hasta encontrar un caracter nulo, osea los msgLen caracteres

	// Imprimamos el paquete para ver cómo quedó
	sendMessage(clients[1] -> socket, package1);

};
