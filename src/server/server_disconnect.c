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
#include "server_disconnect.h"
#include "util.h"
#include "log.h"

void server_disconnect(Client** clients){
	//Package *package = package_init(2, 0);
	char package[2];
	package[0] = 17;
	package[1] = 0;
	sendMessage(clients[0] -> socket, package);

	//send(clients[0] -> socket, package, 2, 0);

	sendMessage(clients[1] -> socket, package);

	//send(clients[1] -> socket, package, 2, 0);
};
