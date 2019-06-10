#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "end_game.h"


void end_game(Client** clients){
	char package[2];
	package[0] = 13;
	package[1] = 0;
	sendMessage(clients[0] -> socket, package);
	sendMessage(clients[1] -> socket, package);
}