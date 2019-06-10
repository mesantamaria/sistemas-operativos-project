#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "ask_new_game.h"


void ask_new_game(Client** clients){
	char package[2];
	package[0] = 15;
	package[1] = 0;

	sendMessage(clients[0]->socket, package);
  sendMessage(clients[1]->socket, package);

}
