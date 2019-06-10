#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "game_winner.h"
#include "ask_new_game.h"
#include "damas/tablero.h"


void game_winner(Client** clients, Tablero* tablero){
	char winner_id = 0;
	if (ganador(tablero, 0)) {
		winner_id = clients[0] -> ID;
		char package[3];
		package[0] = 14;
		package[1] = 1;
		package[2] = winner_id;
		sendMessage(clients[0] -> socket, package);
		sendMessage(clients[1] -> socket, package);
		ask_new_game(clients);


	}
	if (ganador(tablero, 1)) {
		winner_id = clients[1] -> ID;
		char package[3];
		package[0] = 14;
		package[1] = 1;
		package[2] = winner_id;
		sendMessage(clients[0] -> socket, package);
		sendMessage(clients[1] -> socket, package);
		ask_new_game(clients);

	}

}
