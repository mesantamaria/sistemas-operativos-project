#include <unistd.h>  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "init_client.h"
#include "util.h"
#include "return_nickname.h"
#include "start_connection.h"
#include "send_move.h"




int main(int argc, char *argv[])
{
	if (argc < 5)
	{
	    printf("Modo de uso: ./client -i <ip_address> -p <tcp-port> -l\n");
	    return 1;
	}
	int opt;
	char* IP;
	int PORT;  
    while((opt = getopt(argc, argv, "i:p:l")) != -1)  
    {  
        switch(opt)  
        {  
            case 'i':
            	IP = optarg;
            	break;
            case 'p':
            	PORT = atoi(optarg);
            	break;
            case 'l':
            	printf("True\n");  
            	break;
        }  
    }  

	printf("I'm a Client\n");
	int socket;
    //char* IP = argv[2];
	//int PORT = atoi(argv[4]);
	printf("%s %d\n", IP, PORT);

    socket = initializeClient(IP, PORT);

    start_connection(socket);
    Package * msg = receiveMessage(socket);
    free_package(msg);	
    //return 0;


    Package * msg1 = receiveMessage(socket);
	printf("%s\n", msg1 -> payload);
	free_package(msg1);
	return_nickname(socket);

	Package * nickname_oponente = receiveMessage(socket);
	printf("Tu oponente es %s\n", nickname_oponente -> payload);
	free_package(nickname_oponente);	


	Package * conexion_exitosa = receiveMessage(socket);
	if (conexion_exitosa -> ID == 6)
	{
		printf("La conexión ha sido exitosa. El juego ha comenzado\n");
	}
	free_package(conexion_exitosa);	

	
	int ID;
	while(true){
		Package* package = receiveMessage(socket);
		printf("%d\n", package -> ID);
		if (package -> ID == 7)
		{
			printf("Tu puntaje actual es: %d | El puntaje de tu contrincante es: %d\n", package -> payload[0], package -> payload[1]);
		}
		else if (package -> ID == 8)
		{
			printf("Tu ID es %d\n", package -> payload[0]);
			ID = (int) package -> payload[0];
			
		}
		else if (package -> ID == 9)
		{
			print_tablero(package -> payload, ID);
			send_move(socket);
		}
		else if (package -> ID == 11)
		{
			printf("Jugada no válida. Inténtalo de nuevo\n");
		}
		else if (package -> ID == 12)
		{
			printf("Movida exitosa\n");
		}
		else if (package -> ID == 13)
		{
			printf("Se acabo el juego\n");
			free_package(package);
			break;
		}
		free_package(package);
		

	}

	return 0;
	



}
