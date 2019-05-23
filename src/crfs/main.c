#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "estructuras.h"
#include "cr_API.h"
#include "funciones/generales/mount.h"
#include "funciones/generales/ls.h"
#include "funciones/generales/exists.h"
#include "funciones/generales/bitmap.h"
#include "funciones/archivos/open.h"
#include "funciones/archivos/rm.h"



int main(int argc, char *argv[])
{
	if (argc < 2)
	{
	    printf("Modo de uso: ./crfs <disk>]\n");
	    return 0;
	}

	// Obtenemos el nombre del archivo del disco.
	char* disk = argv[1];
	FILE* data = fopen( "simdiskfilled-old.bin", "rb" );
	unsigned char *buffer = malloc(sizeof(unsigned char) * 32 );
	fseek(data, 0, SEEK_SET);  // inicio
	fread(buffer, sizeof(unsigned char), 32, data);


	cr_mount(disk);
	cr_ls("memes");
	//printf("Bitmap:\n");
	//cr_bitmap();
	printf("Exists free: %i\n", cr_exists("/memes/free.jpg"));
	printf("Exists freed: %i\n", cr_exists("/memes/freed.jpg"));
	printf("Exists freed_este_si_que_no: %i\n", cr_exists("/memes/freed_este_si_que_no.jpg"));
	char* stri = "/memes/freed.jpg";
	crFILE* cr_file = cr_open(stri, 'w');
	if (cr_file != NULL)
	{
		printf("Pointer: %u\n", cr_file -> pointer);
		printf("Mode: %c\n", cr_file -> mode);

		free(cr_file);
	}
	printf("Exists freed: %i\n", cr_exists("/memes/freed.jpg"));
	cr_ls("memes");


	printf("------- rm -------\n");
	//cr_bitmap();  // Imprime el bitmap
	printf("Exists /free.jpg: %i\n", cr_exists("/memes/free.jpg"));
	cr_rm("/memes/free.jpg");
	//cr_bitmap();  // Imprime el bitmap
	printf("Exists /free.jpg: %i\n", cr_exists("/memes/free.jpg"));

	// Destruimos todo
	free(buffer);
	fclose(data);

	return 0;
}
