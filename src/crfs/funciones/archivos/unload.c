#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../estructuras.h"
#include "../globals.h"
#include "../generales/exists.h"
#include "read.h"
#include "unload.h"
#include "open.h"

int cr_unload(char* orig, char* dest) {
	if (cr_exists(orig))
	{
		crFILE* cr_file = cr_open(orig, 'r');
		unsigned char *buffer = malloc(sizeof(unsigned char) * 2048);
		cr_read(cr_file, buffer, 2048);
		unsigned int tamano_contenido = (unsigned int)buffer[0] * 256 * 256 * 256 + (unsigned int)buffer[1] * 256 * 256 + (unsigned int)buffer[2] * 256 + (unsigned int)buffer[3];
		printf("Tamaño del archivo: %d Bytes\n", tamano_contenido);
		unsigned char *buffer_contenido = malloc(sizeof(unsigned char) * tamano_contenido);
		cr_read(cr_file, buffer_contenido, tamano_contenido);

		FILE* output = fopen(dest, "wb");
		fwrite(buffer_contenido, sizeof(unsigned char), tamano_contenido, output);

		free(buffer);
		free(buffer_contenido);
		free(cr_file);
		fclose(output);
	}
	else{
		printf("No existe la ruta de origen\n");
	}
	return 0;
}