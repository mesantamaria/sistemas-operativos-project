#include <stdlib.h>
#include <stdio.h>
#include "estructuras.h"

Package* package_init(int ID, int payload_size)
{
	Package* package = malloc(sizeof(Package));

	package -> ID = ID;
	package -> payload_size = payload_size;

	package -> payload = (char*) malloc(sizeof(char) * payload_size);
	return package;
}


void free_package(Package* package)
{
	free(package -> payload);
	free(package);
}