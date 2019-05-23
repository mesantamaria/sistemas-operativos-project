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
#include "funciones/generales/mkdir.h"
#include "funciones/archivos/open.h"
#include "funciones/archivos/close.h"



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

	printf("Bitmap:\n");
	cr_bitmap();
	printf("Exists free: %i\n", cr_exists("/memes/free.jpg"));
	printf("Exists freed: %i\n", cr_exists("/memes/freed.jpg"));
	char* stri = "/memes/freed.jpg";
	crFILE* cr_file = cr_open(stri, 'w');
	if (cr_file != NULL)
	{
		printf("Pointer: %u\n", cr_file -> pointer);
		printf("Mode: %c\n", cr_file -> mode);
	}

	printf("Exists freed: %i\n", cr_exists("/memes/freed.jpg"));
	cr_bitmap();
	cr_ls("memes");
	cr_mkdir("/memes/horas");
	cr_bitmap();
	cr_ls("memes");

	crFILE* cr_file_1 = cr_open("/memes/horas/ar.txt", 'w');
	if (cr_file != NULL)
	{
		printf("Pointer: %u\n", cr_file_1 -> pointer);
		printf("Mode: %c\n", cr_file_1 -> mode);
	}
	cr_close(cr_file_1);

	cr_bitmap();

	printf("mkdir: %i\n", cr_mkdir("/memes/horas/minutos"));

	cr_bitmap();
	// cr_bitmap();  // Imprime el bitmap
	// Destruimos todo
	cr_close(cr_file);
	return 0;
}
