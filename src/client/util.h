#pragma once
#include "estructuras.h"

Package* receiveMessage(int socket);

void sendMessage(int socket, char* package);

int calculate_length(char * input);

void print_package(char * package);

void print_tablero(char* buffer, int ID);

char to_unicode(char estado);