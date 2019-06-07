#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "math.h"
#include "util.h"
#include "init_server.h"


/* Función que inicializa el servidor en el port
con ip */
int* initializeServer(char* ip, int port){
	int welcomeSocket, newSocket;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	int* sockets = (int*) malloc(sizeof(int) * 2);

	/*---- Creación del Socket. Se pasan 3 argumentos ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol (TCP en este caso) */
	welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

  // Pueden buscar como configurar el socket para que libere el puerto una vez que se termine el programa
  
	/*---- Configuración de la estructura del servidor ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number */
	serverAddr.sin_port = htons(port);
	/* Setear IP address como localhost */
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	/* Setear todos los bits del padding en 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	/*---- Bindear la struct al socket ----*/
	bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	/*---- Listen del socket, con un máximo de 5 conexiones (solo como ejemplo) ----*/
	if(listen(welcomeSocket, 2)==0)
		printf("Waiting a client to connect...\n");
	else
		printf("Error\n");

	addr_size = sizeof serverStorage;
  // Servidor queda bloqueado aquí hasta que alguien se conecte.
	sockets[0] = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	printf("Client %d has connected to me!\n", sockets[0]);

	char* input = "What is your nickname?";
	printf("%s\n", input);
	// Calculamos el largo del mensaje ingresado por el humano
	int msgLen = calculate_length(input); //no se debería enviar en el payload el caracter nulo al final del input. Ojo que al imprimir el string sin este caracter les aparecerá un simbolo raro al final
	// Armamos el paquete a enviar
	char package[2+msgLen];
	// Definimos el ID, el payloadSize y copiamos el mensaje
	package[0] = 3;
	package[1] = msgLen;
	strcpy(&package[2], input); //debería copiar hasta encontrar un caracter nulo, osea los msgLen caracteres

	// Imprimamos el paquete para ver cómo quedó
	sendMessage(sockets[0], package);


 	Package* msg = receiveMessage(sockets[0]);





	//sockets[1] = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	//printf("Client %d has connected to me!\n", sockets[1]);

	return sockets;
}