#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "estructuras.h"
#include "init_server.h"




int main(int argc, char *argv[])
{
	if (argc < 5)
	{
	    printf("Modo de uso: ./server -i <ip_address> -p <tcp-port> -l\n");
	    return 1;
	}

	printf("I'm the Server\n");
	int socket;
	char* IP = argv[2];
	int PORT = atoi(argv[4]);
	printf("%s %d\n", IP, PORT);

    socket = initializeServer(IP, PORT);
	return 0;
}
