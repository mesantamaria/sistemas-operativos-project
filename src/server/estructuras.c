#include <stdlib.h>
#include <stdio.h>
#include "estructuras.h"

Package* package_init(char ID, char payload_size)
{
	Package* package = malloc(sizeof(Package));

	package -> ID = ID;
	package -> payload_size = payload_size;

	package -> payload = (char*) malloc(sizeof(char) * payload_size);
	return package;
}


void free_package(Package* package)
{
	free(package -> payload);
	free(package);
}

Client* client_init(int socket, char* nickname)
{
	Client* client = malloc(sizeof(Client));
	client -> socket = socket;
	client -> nickname = nickname;
	client -> puntaje = 0;
	return client;
}

void free_client(Client* client)
{
	free(client);
}