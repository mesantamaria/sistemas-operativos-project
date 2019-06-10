#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "init_server.h"
#include "damas/tablero.h"
#include "damas/utils.h"
#include "damas/jugadas.h"
#include "estructuras.h"
#include "scores.h"
#include "whos_first.h"
#include "board_state.h"
#include "ok_move.h"
#include "end_game.h"
#include "error_move.h"
#include "spread_message.h"
#include "log.h"
#include "server_disconnect.h"
#include "game_winner.h"




int main(int argc, char *argv[])
{
	if (argc < 5)
	{
	    printf("Modo de uso: ./server -i <ip_address> -p <tcp-port> -l\n");
		Tablero* tablero = tablero_init(0);
		print_tablero(tablero);
		jugar(tablero, 5, 1, 4, 2);
		printf("Puntaje 1 = %d\n", puntaje(tablero, 0));
		printf("Puntaje 2 = %d\n", puntaje(tablero, 1));
		jugar(tablero, 2, 0, 3, 1);
		printf("Puntaje 1 = %d\n", puntaje(tablero, 0));
		printf("Puntaje 2 = %d\n", puntaje(tablero, 1));
		jugar(tablero, 4, 2, 2, 0);
		printf("Puntaje 1 = %d\n", puntaje(tablero, 0));
		printf("Puntaje 2 = %d\n", puntaje(tablero, 1));
		destroy_tablero(tablero);
	    return 1;
	}

	int opt;
	char* IP;
	int PORT;
	LOG = 0;
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
            	LOG = 1;
            	break;
        }
    }

	printf("I'm the Server\n");
	Package* inicio = package_init(-1, 0);
	log_event(inicio);
	free_package(inicio);

	//char* IP = argv[2];
	//int PORT = atoi(argv[4]);
	printf("%s %d\n", IP, PORT);


	Client** clients = initializeServer(IP, PORT);
	scores(clients);
	int start_player = whos_first(clients);
	Tablero* tablero = tablero_init(start_player);
	print_tablero(tablero);
	int j = 0;
	int condicion = 1;
	int disconnected = 0;
	while(condicion)
	{
		while(j < 1){  // Número de rondas. Cambiar a True para simular juego completo
			while(true){
				board_state(clients[start_player], tablero);
				Package* move_package = receiveMessage(clients[start_player] -> socket);
				//printf("Posiciones inicio %s |\n", move_package -> payload);
				if (move_package -> ID == 19)
				{
					spread_message(clients[1 - start_player], move_package);
					free_package(move_package);
				}
				else if (move_package -> ID == 17)
				{
					disconnected = 1;
					free_package(move_package);
					break;
				}
				else {
					if (jugar(tablero, move_package -> payload[1] - 49, move_package -> payload[0] - 65, move_package -> payload[3] - 49, move_package -> payload[2] - 65)){
						clients[start_player] -> puntaje = puntaje(tablero, start_player);
						ok_move(clients[start_player] -> socket);
						free_package(move_package);
						break;
					}
					else {
						error_move(clients[start_player] -> socket);
						free_package(move_package);
					}
				}
			}
			if (ganador(tablero, start_player) || disconnected == 1) {
				break;
			}
			scores(clients);
			start_player = tablero -> turno;
			j ++;
		}
		if (disconnected == 1)
		{
			break;
		}

		end_game(clients);
		board_state(clients[0], tablero);
		board_state(clients[1], tablero);
		game_winner(clients, tablero);
		Package* nuevo_package1 = receiveMessage(clients[0] -> socket);
		Package* nuevo_package2 = receiveMessage(clients[1] -> socket);

		if(((int)nuevo_package1->payload==1) && ((int)nuevo_package2->payload==1))
		{
			condicion=1;
			destroy_tablero(tablero);
			Tablero* tablero = tablero_init(start_player);
			print_tablero(tablero);
		}
		else
		{
			condicion=0;
		}
		scores(clients);

	}

	server_disconnect(clients);

	// Liberamos todo
	destroy_tablero(tablero);
	for (int i = 0; i < 2; ++i)
	{
		free_client(clients[i]);
	}
	free(clients);


	//while(true)
	//{

	//}


	return 0;
}
