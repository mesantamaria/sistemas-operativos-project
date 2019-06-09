#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "init_server.h"
#include "damas/tablero.h"
#include "damas/utils.h"
#include "damas/jugadas.h"




int main(int argc, char *argv[])
{
	if (argc < 5)
	{
	    printf("Modo de uso: ./server -i <ip_address> -p <tcp-port> -l\n");
		Tablero* tablero = tablero_init();
		print_tablero(tablero);
		jugar(tablero, 5, 1, 4, 2);
		jugar(tablero, 2, 0, 3, 1);
		jugar(tablero, 4, 2, 2, 0);
		char* buffer[64];
		tablero_to_char(buffer, tablero);
		printf("%s\n", buffer);
		destroy_tablero(tablero);
	    return 1;
	}

	printf("I'm the Server\n");
	int* sockets;
	char* IP = argv[2];
	int PORT = atoi(argv[4]);
	printf("%s %d\n", IP, PORT);

	sockets = initializeServer(IP, PORT);
	free(sockets);
	return 0;
}
