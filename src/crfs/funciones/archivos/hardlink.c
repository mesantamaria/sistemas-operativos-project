#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../estructuras.h"
#include "../globals.h"

int cr_hardlink(char* route, char* route_d){

	FILE* data = fopen(disk_path, "r+" );
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 32);

	int ind;
	for (int i = strlen(route) - 1; i >= 0; --i)
	{
		if (route[i] == '/')
		{
			ind = i;
			break;
		}
	}
	char dir_route_2[strlen(route_d) + 1];
	strcpy(dir_route_2, route_d);
	char dir_route[strlen(route) + 1];
	char name[28];
	for (int i = 0; i < ind; ++i)
	{
		dir_route[i] = route[i];
	}
	dir_route[ind] = '\0';
	for (int i = ind + 1; i < strlen(route) + 1; ++i)
	{
		name[i - (ind + 1)] = route[i];
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
			fclose(data);
			printf("La ruta de origen no existe.\n");
			return 0;
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
	if (found == false)
	{
		free(buffer);
		fclose(data);
		printf("Archivo no existe en la ruta de origen especificada.\n");
		return 0;
	}
	else
	{
		//el último buffer es el que hay que copiar en nueva ruta
		unsigned char *buffer_2 = malloc(sizeof( unsigned char ) * 32);
		char* folder_2 = strtok(dir_route_2, "/");
		pointer = 0;
		found = false;
		while(folder_2 != NULL){
			found = false;
			for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
				fseek(data, 32 * i + pointer, SEEK_SET);
				fread(buffer_2, sizeof(unsigned char), 32, data);
				if (buffer_2[0] == (unsigned char)2 && strcmp(folder_2, (const char*) (buffer_2 + 1)) == 0 )
				{
					pointer = ((unsigned int)buffer_2[30] * 256 + (unsigned int)buffer_2[31]) * 2048;
					found = true;
					break;
				}
			}
			if (!found)
			{
				free(buffer);
				free(buffer_2);
				fclose(data);
				printf("La ruta de destino no existe.\n");
				return 0;
			}
			folder_2 = strtok(NULL, "/");
		}
		found = false;
		for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
			fseek(data, 32 * i + pointer, SEEK_SET);
			fread(buffer_2, sizeof(unsigned char), 32, data);
			if (buffer_2[0] == (unsigned char)4 && strcmp(name, (const char*) (buffer_2 + 1)) == 0 )
			{
				found = true;
				break;
			}
		}
		if (found)
		{
			free(buffer_2);
			free(buffer);
			fclose(data);
			printf("Ya existe un archivo con ese nombre en la ruta de destino especificada.\n");
			return 0;
		}
		else
		{
			bool copied = false;
			for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
				fseek(data, 32 * i + pointer, SEEK_SET);
				fread(buffer_2, sizeof(unsigned char), 32, data);
				if (buffer_2[0] == (unsigned char)1)
				{
					fseek(data, 32 * i + pointer, SEEK_SET);
					fwrite(buffer, sizeof(unsigned char), 32, data);
					copied = true;
					break;
				}
			}
			if (copied)
			{
				unsigned int value;
				unsigned char *buffer_3 = malloc(sizeof( unsigned char ) * 4);
				pointer = ((unsigned int)buffer[30] * 256 + (unsigned int)buffer[31]) * 2048;
				fseek(data, pointer + 4, SEEK_SET);
				fread(buffer_3, sizeof(unsigned char), 4, data);
				value = (unsigned int)buffer_3[0] * 256 * 256 * 256 + 
						(unsigned int)buffer_3[1] * 256 * 256 + 
						(unsigned int)buffer_3[2] * 256 + 
						(unsigned int)buffer_3[3] + 1;
				buffer_3[0] = (value >> 24) & 0xFF;
				buffer_3[1] = (value >> 16) & 0xFF;
				buffer_3[2] = (value >> 8) & 0xFF;
				buffer_3[3] = value & 0xFF;
				fseek(data, pointer + 4, SEEK_SET);
				fwrite(buffer_3, sizeof(unsigned char), 4, data);

				free(buffer_2);
				free(buffer_3);
				free(buffer);
				fclose(data);
				return 1;
			}
			else
			{
				free(buffer_2);
				free(buffer);
				fclose(data);
				printf("No hay espacio para una nueva entrada.\n");
				return 0;
			}
		}
	}
	free(buffer);
	fclose(data);
	return 0;
}