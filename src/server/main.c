#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "init_server.h"
#include "damas/tablero.h"
#include "damas/utils.h"




int main(int argc, char *argv[])
{
	if (argc < 5)
	{
	    printf("Modo de uso: ./server -i <ip_address> -p <tcp-port> -l\n");
<<<<<<< HEAD
		Tablero* tablero = tablero_init();
		print_tablero(tablero);
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
=======
	    return 0;
	}

	char *ip = argv[2];
	int port = argv[4];
	bool log = false;
	if (argc == 6)
	{
		log = true;
	}

>>>>>>> protocolos
	return 0;
}
