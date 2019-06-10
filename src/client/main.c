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
#include "send_message.h"
#include "client_disconnect.h"
#include "answer_new_game.h"



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

	int terminado = 0;


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
			if (!terminado) {
				printf("¿Qué desea hacer?\n");
				printf("1 Jugar\n");
				printf("2 Enviar mensaje\n");
				printf("3 Desconectarse\n");
				printf("Ingrese el número de su opción: \n");
				int input;
				scanf("%d", &input);
				printf("\n");
				printf("   Ingresaste: %i\n", input);
				if (input == 1)
				{
					send_move(socket);
				}
				else if (input == 2)
				{
					send_message(socket);
				}
				else if (input == 3)
				{
					client_disconnect(socket);
				}
			}
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
			terminado = 1;
			free_package(package);
		}
		else if (package -> ID == 14)
		{
			int winner = (int) package -> payload[0];
			if (winner == 0) {
				printf("Hubo un empate\n");
			}
			else if (winner == ID) {
				printf("Has ganado! Felicitaciones!\n");
			}
			else {
				printf("Lo siento, has perdido :(\n");
			}
			free_package(package);
		}
		else if (package -> ID == 15)
		{

			printf("¿Deseas jugar nuevamente?\n");
			printf("1 Si\n");
			printf("0 No\n");

			printf("Ingrese el número de su opción: \n");
			int input;
			scanf("%d", &input);
			printf("\n");
			printf("   Ingresaste: %i\n", input);
			answer_new_game(socket, input);
		}

		else if (package -> ID == 17)
		{
			printf("Juego desconectado\n");
			//free_package(package);
			break;
		}
		else if (package -> ID == 18)
		{
			printf("El package enviado estaba corrupto\n");
			//free_package(package);
		}

		else if (package -> ID == 20)
		{
			printf("Mensaje de tu oponente:\n");
			printf("%s\n", package -> payload);
		}
		free_package(package);

	}

	return 0;




}
