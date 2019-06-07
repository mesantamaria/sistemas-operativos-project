#pragma once

typedef struct Package
{
	char ID;
	char payload_size;
	char* payload;
} Package;

Package* package_init(char ID, char payload_size);
void free_package(Package* package);

typedef struct  Client
{
	int socket;
	char nickname[255];
	int puntaje;
	char* color;
} Client;

Client* client_init(int socket, char* nickname);
void free_client(Client* client);