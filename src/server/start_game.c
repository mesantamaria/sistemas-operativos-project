#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "math.h"
#include "estructuras.h"
#include "start_game.h"

void start_game(int socket){

	char package[2];
	package[0] = 6;
	package[1] = 0;
	send(socket, package, 2, 0);
};
