#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "../../estructuras.h"
#include "../globals.h"
#include "../generales/exists.h"
#include "read.h"
#include "unload.h"
#include "open.h"


int unload_file(char* orig, char* dest){
	
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


int cr_unload(char* orig, char* dest) {
	// Retorna cantidad de archivos traspasados correctamente
	if (access(dest, F_OK) == -1)
	{
		mkdir(dest);
	}
	
	if (cr_exists(orig))
	{
		FILE* data = fopen(disk_path, "rb" );
		unsigned char *buffer = malloc(sizeof( unsigned char ) * 32);
		char copy[strlen(orig)];
		strcpy(copy, orig);
		unsigned int pointer = 0;
		char* folder = strtok(copy, "/");
		bool found = false;
		while(strcmp(orig, "") != 0 && folder != NULL){
			found = false;
			// printf("FOLDER: %s\n", folder);
			for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
				fseek(data, 32 * i + pointer, SEEK_SET);
				fread(buffer, sizeof(unsigned char), 32, data);
				if (buffer[0] != (unsigned char)1 && strcmp(folder, (const char*) (buffer + 1)) == 0 )
				{
					pointer = ((unsigned int)buffer[30] * 256 + (unsigned int)buffer[31]) * 2048;
					found = true;
					break;
				}
			}
			folder = strtok(NULL, "/");
		}
		if (buffer[0] == (unsigned char)2)
		{
			// printf("Es un directorio\n");
			folder = (const char*) (buffer + 1);
			//char destination[strlen(dest) + strlen(folder) + 1];
			char *destination = (char*)malloc(sizeof(char) * (strlen(dest) + strlen(folder) + 2));
			strcpy(destination, dest);
			strcat(destination, "/");
			strcat(destination, folder);
			//printf("%s %s\n", destination, dest);
			for(int i = 0; i < 64; i++) {
				fseek(data, 32 * i + pointer, SEEK_SET);
				fread(buffer, sizeof(unsigned char), 32, data);
				if (buffer[0] != (unsigned char)1)
				{
					char origen[strlen(orig) + strlen(folder) + 1];
					strcpy(origen, orig);
					strcat(origen, "/");
					strcat(origen, folder);
					// printf("%s %s\n", origen, destination);
					cr_unload(origen, destination);
				}
			}
			free(destination);

		}
		else if (buffer[0] == (unsigned char)4){
			// printf("Es un archivo\n");
			folder = (const char*) (buffer + 1);  // file
			char output_path[strlen(folder) + 1 + strlen(dest)];
			strcpy(output_path, dest);
			strcat(output_path, "/");
			strcat(output_path, folder);
			//printf("Se escribe en %s\n", output_path);
			
			unload_file(orig, output_path);
		}
		free(buffer);
		fclose(data);
	}
	else{
		printf("No existe la ruta de origen\n");
	}
	return 0;
}