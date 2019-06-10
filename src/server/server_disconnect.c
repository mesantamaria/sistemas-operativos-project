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

void server_disconnect(Client** clients){
	//Package *package = package_init(2, 0);
	char package[2];
	package[0] = 17;
	package[1] = 0;
	send(clients[0] -> socket, package, 2, 0);

	char package2[2];
	package2[0] = 17;
	package2[1] = 0;
	send(clients[1] -> socket, package2, 2, 0);

 	//send_package(package, tipo);
};