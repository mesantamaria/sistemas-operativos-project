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
#include "connection_established.h"
#include "init_server.h"
#include "ask_nickname.h"
#include "opponent_found.h"
#include "start_game.h"


/* Función que inicializa el servidor en el port
con ip */
Client** initializeServer(char* ip, int port){
	int welcomeSocket;
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
	Package* mensaje_conectado = receiveMessage(sockets[0]);
	printf("%d\n", mensaje_conectado -> ID);
	free_package(mensaje_conectado);
	connection_established(sockets[0]);

	ask_nickname(sockets[0]);

 	Package* nickname_1 = receiveMessage(sockets[0]);

 	sockets[1] = accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size);
	printf("Client %d has connected to me!\n", sockets[1]);

	Package* mensaje_conectado1 = receiveMessage(sockets[1]);
	printf("%d\n", mensaje_conectado1 -> ID);
	free_package(mensaje_conectado1);
	connection_established(sockets[1]);

	ask_nickname(sockets[1]);

 	Package* nickname_2 = receiveMessage(sockets[1]);

 	Client** clients = malloc(sizeof(Client*) * 2);
 	char name1[255];
 	char name2[255];
 	strcpy(name1, nickname_1 -> payload);
 	strcpy(name2, nickname_2 -> payload);
 	clients[0] = client_init(sockets[0], name1);
 	clients[1] = client_init(sockets[1], name2);
 	free_package(nickname_1);
 	free_package(nickname_2);
 	

 	opponent_found(clients);

 	for (int i = 0; i < 2; ++i)
 	{
 		start_game(clients[i] -> socket);
 	}

 	free(sockets);
	return clients;
}