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
#include "connection_established.h"

void connection_established(int socket){
	//Package *package = package_init(2, 0);
	char package[2];
	package[0] = 2;
	package[1] = 0;
	send(socket, package, 2, 0);

 	//send_package(package, tipo);
};
