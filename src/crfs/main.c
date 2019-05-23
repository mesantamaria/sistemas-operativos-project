#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "estructuras.h"
#include "cr_API.h"
#include "funciones/generales/mount.h"
#include "funciones/generales/ls.h"
#include "funciones/generales/exists.h"
#include "funciones/generales/bitmap.h"
#include "funciones/archivos/open.h"
#include "funciones/archivos/rm.h"
#include "funciones/utils.h"
#include "funciones/archivos/read.h"



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
	//cr_ls("memes");
	//printf("Bitmap:\n");

	//cr_ls("memes");
	// cr_bitmap();  // Imprime el bitmap
	crFILE* cr_file = cr_open("/thanos/thanos.gif", 'r');
	unsigned char *buffer2 = malloc(sizeof(unsigned char) * 2048 * 9 );
	//fseek(data, cr_file -> pointer, SEEK_SET);
	//fread(buffer2, sizeof(unsigned char), 2048, data);
	//printf("%d\n", (unsigned int)buffer2[8] * 256 * 256 * 256 + (unsigned int)buffer2[9] * 256 * 256 + (unsigned int)buffer2[10] * 256 + (unsigned int)buffer2[11]);
	int a = cr_read(cr_file, buffer2, 2048);
	int b = cr_read(cr_file, &buffer2[2048], 2048 * 8 - 1);
	printf("%d %d\n", a, b);
	printf("%d\n", (unsigned int)buffer2[0] * 256 * 256 * 256 + (unsigned int)buffer2[1] * 256 * 256 + (unsigned int)buffer2[2] * 256 + (unsigned int)buffer2[3]);
	free(buffer2);
	free(cr_file);

	cr_ls("memes");

	printf("------- rm -------\n");
	cr_bitmap();  // Imprime el bitmap
	printf("Exists /free.jpg: %i\n", cr_exists("/memes/free.jpg"));
	cr_rm("/memes/free.jpg");
	cr_bitmap();  // Imprime el bitmap
	printf("Exists /free.jpg: %i\n", cr_exists("/memes/free.jpg"));

	// Destruimos todo
	free(buffer);
	fclose(data);

	return 0;
}
