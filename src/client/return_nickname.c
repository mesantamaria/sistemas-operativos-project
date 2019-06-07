#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "return_nickname.h"

void return_nickname(int socket){

	/*
	char size = strlen(nickname) + 1;
	Package *package = package_init(4, size);
	package->payload = nickname;
	//send_package(package,"s");
	*/

	char input[255]; // definimos un arreglo estúpidamente grande
	printf("\nEnter your nickname: ");
	scanf("%s", input);
	printf("\n");
	printf("   Ingresaste: %s\n", input);

	// Calculamos el largo del mensaje ingresado por el humano
	int msgLen = calculate_length(input); //no se debería enviar en el payload el caracter nulo al final del input. Ojo que al imprimir el string sin este caracter les aparecerá un simbolo raro al final

	// Armamos el paquete a enviar
	char package[2+msgLen];
	// Definimos el ID, el payloadSize y copiamos el mensaje
	package[0] = 4;
	package[1] = msgLen;
	strcpy(&package[2], input); //debería copiar hasta encontrar un caracter nulo, osea los msgLen caracteres

	// Imprimamos el paquete para ver cómo quedó
	print_package(package);

	sendMessage(socket, package);




};
