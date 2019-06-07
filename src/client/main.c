#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "init_client.h"
#include "util.h"
#include "start_connection.h"




int main(int argc, char *argv[])
{
	if (argc < 5)
	{
	    printf("Modo de uso: ./client -i <ip_address> -p <tcp-port> -l\n");
	    return 1;
	}

	printf("I'm a Client\n");
	int socket;
    char* IP = argv[2];
	int PORT = atoi(argv[4]);
	printf("%s %d\n", IP, PORT);

    socket = initializeClient(IP, PORT);
    start_connection(socket);
    Package * msg = receiveMessage(socket);
    free_package(msg);	
    return 0;


    while(true)
    {
		Package * msg = receiveMessage(socket);
		printf("packageeee: %i\n", msg -> ID);
		printf("package payload: %s\n", msg -> payload);
	}




	return 0;
}
