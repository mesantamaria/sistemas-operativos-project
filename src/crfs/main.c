#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estructuras.h"
#include "cr_API.h"
#include "funciones/generales/mount.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
	{
	    printf("Modo de uso: ./crfs <disk>]\n");
	    return 0;
	}

	// Obtenemos el nombre del archivo del disco.
	char* disk = argv[1];
	cr_mount(disk);

	// Destruimos todo

	return 0;
}
