#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "rm.h"
#include "../globals.h"
#include "../utils.h"

int cr_rm(char* path) {
	FILE* data = fopen(disk_path, "r+" );

	unsigned int file_pointer = get_pointer_from_path(path, data);
	unsigned int file_pointers = file_pointer + 8;

	borrar_bloques_punteros(file_pointers, 500, data);

	unsigned int indirect_pointers = file_pointers + 2000;
	borrar_bloques_punteros_indirectos(indirect_pointers, 10, data);
	borrar_bloque(file_pointer, data);

	borrar_puntero_directorio(path, data);

	fclose(data);

	return 0;
}

void borrar_bloques_punteros_indirectos(unsigned int punteros, unsigned int  n_punteros, FILE* data) {
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 4);
	unsigned int pointer = 0;
	int i, j;
	for (i = 0; i < n_punteros; i++) {
		pointer = 0;
		fseek(data, punteros + 4 * i, SEEK_SET);
		fread(buffer, sizeof(unsigned char), 4, data);
		for (j = 2; j < 4; j++) {
			pointer += (unsigned int)buffer[j] << 8*(3-j);
		}
		pointer *= 2048;
		if (pointer != 0) {
			borrar_bloques_punteros(pointer, 524, data);
			borrar_bloque(pointer, data);
		}
	}
	free(buffer);
}

void borrar_bloques_punteros(unsigned int punteros, unsigned int  n_punteros, FILE* data) {
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 4);
	unsigned int pointer = 0;
	int i, j;
	for (i = 0; i < n_punteros; i++) {
		pointer = 0;
		fseek(data, punteros + 4 * i, SEEK_SET);
		fread(buffer, sizeof(unsigned char), 4, data);
		for (j = 2; j < 4; j++) {
			pointer += (unsigned int)buffer[j] << 8*(3-j);
		}
		pointer *= 2048;
		if (pointer != 0) {
			borrar_bloque(pointer, data);
		}
	}
	free(buffer);
}

void borrar_bloque(unsigned int pointer, FILE* data) {
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 2048);
	int i;
	for (i = 0; i < 2048; i++) {
		buffer[i] = 0;
	}
	fseek(data, pointer, SEEK_SET);
	fwrite(buffer, sizeof(unsigned char), 2048, data);
	free(buffer);
	printf("%d\n", pointer/2048);
	change_bitmap(pointer / 2048, 0, data);
}

void borrar_puntero_directorio(char* path, FILE* data) {
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 32);

	int ind;
	for (int i = strlen(path) - 1; i >= 0; --i)
	{
		if (path[i] == '/')
		{
			ind = i;
			break;
		}
	}
	char dir_route[strlen(path) + 1];
	char name[28];
	for (int i = 0; i < ind; ++i)
	{
		dir_route[i] = path[i];
	}
	dir_route[ind] = '\0';
	for (int i = ind + 1; i < strlen(path) + 1; ++i)
	{
		name[i - (ind + 1)] = path[i];
	}

	unsigned int pointer = 0;
	char* folder = strtok(dir_route, "/");
	bool found = false;

	while(folder != NULL){
		found = false;
		for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
			fseek(data, 32 * i + pointer, SEEK_SET);
			fread(buffer, sizeof(unsigned char), 32, data);
			if (buffer[0] == (unsigned char)2 && strcmp(folder, (const char*) (buffer + 1)) == 0 )
			{
				pointer = ((unsigned int)buffer[30] * 256 + (unsigned int)buffer[31]) * 2048;
				found = true;
				break;
			}
		}
		if (!found)
		{
			free(buffer);
			printf("La ruta no existe.\n");
			return NULL;
		}
		folder = strtok(NULL, "/");
	}
	found = false;
	for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
		fseek(data, 32 * i + pointer, SEEK_SET);
		fread(buffer, sizeof(unsigned char), 32, data);
		if (buffer[0] == (unsigned char)4 && strcmp(name, (const char*) (buffer + 1)) == 0 )
		{
			fseek(data, 32 * i + pointer, SEEK_SET);
			buffer[0] = (unsigned char)1;
			fwrite(buffer, sizeof(unsigned char), 32, data);
			break;
		}
	}
	free(buffer);
}