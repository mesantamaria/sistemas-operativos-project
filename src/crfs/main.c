#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estructuras.h"
#include "cr_API.h"
#include "funciones/generales/mount.h"
#include "funciones/generales/ls.h"



int main(int argc, char *argv[])
{
	if (argc < 2)
	{
	    printf("Modo de uso: ./crfs <disk>]\n");
	    return 0;
	}

	// Obtenemos el nombre del archivo del disco.
	char* disk = argv[1];
	FILE* data = fopen( "simdiskfilled.bin", "rb" );
	unsigned char *buffer = malloc(sizeof(unsigned char) * 32 );
	fseek(data, 0, SEEK_SET);  // inicio
	fread(buffer, sizeof(unsigned char), 32, data);
	

	cr_mount(disk);
	cr_ls("memes");
	
	// Destruimos todo
	free(buffer);
	fclose(data);

	return 0;
}
