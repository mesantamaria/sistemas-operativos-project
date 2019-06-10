#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "ok_move.h"


void ok_move(int socket){
	char package[2];
	package[0] = 12;
	package[1] = 0;
	sendMessage(socket, package);
}