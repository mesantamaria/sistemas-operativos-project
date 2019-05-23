#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "../../estructuras.h"
#include "../globals.h"

int cr_mkdir(char *route) {
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
			printf("La ruta no existe.\n");
			return 0;
		}
		folder = strtok(NULL, "/");
	}

	found = false;
	for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
		fseek(data, 32 * i + pointer, SEEK_SET);
		fread(buffer, sizeof(unsigned char), 32, data);
		if (buffer[0] == (unsigned char)2 && strcmp(name, (const char*) (buffer + 1)) == 0 )
		{
			pointer = ((unsigned int)buffer[30] * 256 + (unsigned int)buffer[31]) * 2048;
			found = true;
			break;
		}
	}

	if (found)
	{
		free(buffer);
		fclose(data);
		printf("Directorio ya existe en la ruta especificada.\n");
		return 0;
	}
	else
	{
		unsigned int new_pointer;
		for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
			fseek(data, 32 * i + pointer, SEEK_SET);
			fread(buffer, sizeof(unsigned char), 32, data);
			if (buffer[0] == (unsigned char)1)
			{
				//recorrer bitmap
				unsigned char *buffer_bitmap = malloc(sizeof( unsigned char ) * 8192);  // 2048 * 4 = 8192
				fseek(data, 2048, SEEK_SET);  // Bloques de Bitmap parten desde Bloque 1
				fread(buffer_bitmap, sizeof(unsigned char), 8192, data);  // Bloques de Bitmap desde Bloque 1 al 4
				unsigned int value;
				unsigned int new_value;
				int k;
				int bloque_0 = 0;
				int bit_changed = 0;
				int j_pointer = 0;
				bool found_0 = false;
				for (int j = 0; j < 8192; ++j)
				{
					bit_changed = 0;
					value = (unsigned int) buffer_bitmap[j];
					for (int b = 7; b >= 0; --b)
					{
						k = value >> b;
						if (k & 1)
						{
							bloque_0++;
						}
						else
						{
							bit_changed = b;
							found_0 = true;
							break;
						}
					}
					if (found_0)
					{
						break;
					}
					j_pointer++;
				}
				if (found_0)
				{
					new_value = value + pow(2, bit_changed);
					fseek(data, 2048 + j_pointer, SEEK_SET);
					fputc((unsigned char)new_value, data);
					free(buffer_bitmap);
					//bloque_0 = numero de primer bloque desocupado
					//actualizar bitmap
					//cambiar buffer_bitmap[ind] para luego hacer fputc
					buffer[0] = (unsigned char)2 & 0xff;
					//actualizar nombre
					for (int c = 1; c < strlen(name) + 2; ++c)
					{
						buffer[c] = (unsigned char)name[c - 1];
					}
					buffer[31] = (unsigned char) bloque_0 & 0xff;
					buffer[30] = (unsigned char) bloque_0 >> 8;
					fseek(data, 32 * i + pointer, SEEK_SET);
					fwrite(buffer, sizeof(unsigned char), 32, data);
					new_pointer = ((unsigned int)buffer[30] * 256 + (unsigned int)buffer[31]) * 2048;
					buffer[0] = (unsigned char)1 & 0xff;
					for (int n = 0; n < 64; ++n)
					{
						fseek(data, 32 * n + new_pointer, SEEK_SET);
						fputc(buffer[0], data);
					}
					free(buffer);
					fclose(data);
					return 1;
				}
				else
				{
					printf("No hay espacio para nuevo directorio\n");
					free(buffer);
					fclose(data);
					return 0;
				}
			}
		}
	}
	free(buffer);
	fclose(data);
	return 0;
}