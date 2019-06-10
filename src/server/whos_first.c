#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "util.h"
#include "scores.h"


int whos_first(Client** clients){
	srand(time(NULL));   // Initialization, should only be called once.
	int start_player = rand() % 2;
	char package[3];
    package[0] = 8;
    package[1] = 1;
    package[2] = 1;
	sendMessage(clients[start_player] -> socket, package);
	clients[start_player] -> ID = 1;
	int index = (start_player + 1) % 2;
	package[2] = 2;
	sendMessage(clients[index] -> socket, package);
	clients[index] -> ID = 2;
	return start_player;
}
