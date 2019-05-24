#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "globals.h"
#include "utils.h"

void* get_pointer_from_path(char* path, FILE* data) {
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
			pointer = ((unsigned int)buffer[30] * 256 + (unsigned int)buffer[31]) * 2048;
			found = true;
			break;
		}
	}
	free(buffer);
	return pointer;
}

void change_bitmap(unsigned int bloque, int value, FILE* data) {
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 8192);  // 2048 * 4 = 8192
	fseek(data, 2048, SEEK_SET);  // Bloques de Bitmap parten desde Bloque 1
	fread(buffer, sizeof(unsigned char), 8192, data);  // Bloques de Bitmap desde Bloque 1 al 4
	if (value == 0) {
		buffer[bloque / 8] &= ~(1UL << (bloque % 8));
	}
	else {
		buffer[bloque / 8] |= 1UL << (bloque % 8);
	}
	fseek(data, 2048, SEEK_SET);  // Bloques de Bitmap parten desde Bloque 1
	fwrite(buffer, sizeof(unsigned char), 8192, data);
	free(buffer);
}

unsigned int get_pointer(unsigned int entry, FILE* data) {
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 4);
	unsigned int pointer = 0;
	int j;
	pointer = 0;
	fseek(data, entry, SEEK_SET);
	fread(buffer, sizeof(unsigned char), 4, data);
	for (j = 2; j < 4; j++) {
		pointer += (unsigned int)buffer[j] << 8*(3-j);
	}
	pointer *= 2048;
	free(buffer);
	return pointer;
}
