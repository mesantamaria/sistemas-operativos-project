#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "error_move.h"


void error_move(int socket){
	char package[2];
	package[0] = 11;
	package[1] = 0;
	sendMessage(socket, package);
}