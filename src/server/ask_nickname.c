#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "ask_nickname.h"

void ask_nickname(int socket){
	//Package *package = package_init(3, 0);
	//send_package(package, tipo);
	char* input = "What is your nickname?";
	// Calculamos el largo del mensaje ingresado por el humano
	int msgLen = calculate_length(input); //no se debería enviar en el payload el caracter nulo al final del input. Ojo que al imprimir el string sin este caracter les aparecerá un simbolo raro al final
	// Armamos el paquete a enviar
	char package[2+msgLen];
	// Definimos el ID, el payloadSize y copiamos el mensaje
	package[0] = 3;
	package[1] = msgLen;
	strcpy(&package[2], input); //debería copiar hasta encontrar un caracter nulo, osea los msgLen caracteres

	// Imprimamos el paquete para ver cómo quedó
	sendMessage(socket, package);
};
