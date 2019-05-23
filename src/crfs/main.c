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
#include "funciones/generales/mkdir.h"
#include "funciones/archivos/open.h"
#include "funciones/archivos/close.h"
#include "funciones/archivos/rm.h"
#include "funciones/utils.h"
#include "funciones/archivos/read.h"
#include "funciones/archivos/unload.h"



int main(int argc, char *argv[])
{
	if (argc < 2)
	{
	    printf("Modo de uso: ./crfs <disk>]\n");
	    return 0;
	}

	// Obtenemos el nombre del archivo del disco.
	int mode = atoi(argv[2]);
	char* disk = argv[1];


	cr_mount(disk);
	//cr_ls("memes");
	//printf("Bitmap:\n");

	//cr_ls("memes");
	// cr_bitmap();  // Imprime el bitmap

	//cr_ls("memes");



	if (mode == 3)
	{
		printf("------- rm -------\n");
		printf("Exists /free.jpg: %i\n", cr_exists("/memes/free.jpg"));
		cr_rm("/memes/free.jpg");
		printf("Exists /free.jpg: %i\n", cr_exists("/memes/free.jpg"));
	}
	else if (mode == 4)
	{
		crFILE* cr_file = cr_open("/thanos/thanos.gif", 'r');
		unsigned char *buffer2 = malloc(sizeof(unsigned char) * 2048 * 9 );
		//fseek(data, cr_file -> pointer, SEEK_SET);
		//fread(buffer2, sizeof(unsigned char), 2048, data);
		//printf("%d\n", (unsigned int)buffer2[8] * 256 * 256 * 256 + (unsigned int)buffer2[9] * 256 * 256 + (unsigned int)buffer2[10] * 256 + (unsigned int)buffer2[11]);
		//int a = cr_read(cr_file, buffer2, 2048);
		//int b = cr_read(cr_file, &buffer2[2048], 2048);
		//printf("%d %d\n", a, b);
		//printf("%d\n", (unsigned int)buffer2[0] * 256 * 256 * 256 + (unsigned int)buffer2[1] * 256 * 256 + (unsigned int)buffer2[2] * 256 + (unsigned int)buffer2[3]);
		free(buffer2);
		free(cr_file);
		cr_ls("");
		cr_unload("/SSBS.mp3", "cancion.mp3");
		//cr_unload("/thanos/thanos.gif", "thanos.gif");
		//cr_unload("/germy.txt", "germy.txt");
		//cr_unload("/Program in C.mkv", "Program in C.mkv");
		//cr_unload("/free.jpg", "free.jpg");

	}
	else if (mode == 1)
	{
		printf("------- memes -------\n");
		cr_ls("/memes");
		crFILE* cr_file = cr_open("/memes/for.jpg", 'r');
		printf("------- memes -------\n");
		cr_ls("/memes");
		crFILE* cr_file_1 = cr_open("/memes/fortress.jpg", 'w');
		printf("------- memes -------\n");
		cr_ls("/memes");
		cr_mkdir("/memes/pizza");
		printf("------- memes -------\n");
		cr_ls("/memes");
		cr_mkdir("/memes/pizza");
		printf("------- memes -------\n");
		cr_ls("/memes");
		crFILE* cr_file_2 = cr_open("/memes/pizza/gol.txt", 'w');
		printf("------- memes/pizza -------\n");
		cr_ls("/memes/pizza");
		cr_rm("/memes/pizza/gol.txt");
		printf("------- memes/pizza -------\n");
		cr_ls("/memes/pizza");
		crFILE* cr_file_3 = cr_open("/memes/pizza/gol.txt", 'w');
		printf("------- memes/pizza -------\n");
		cr_ls("/memes/pizza");
		crFILE* cr_file_4 = cr_open("/memes/pizza/gol.txt", 'w');



		cr_close(cr_file);
		cr_close(cr_file_1);
		cr_close(cr_file_2);
		cr_close(cr_file_3);
		cr_close(cr_file_4);

	}
	return 0;
}
