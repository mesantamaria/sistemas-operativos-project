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
#include "start_connection.h"
#include "util.h"

void start_connection(int socket){
	//Package *package = package_init(1, 0);
	char package[2];
	package[0] = 1;
	package[1] = 0;
	sendMessage(socket, package);

	//send(socket, package, 2, 0);


	//send_package(package,"s");
}
