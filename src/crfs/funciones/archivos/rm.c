#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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
		for (j = 0; j < 4; j++) {
			pointer += (unsigned int)buffer[j] << 8*(3-j);
		}
		borrar_bloques_punteros(pointer, data, data);
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
		for (j = 0; j < 4; j++) {
			pointer += (unsigned int)buffer[j] << 8*(3-j);
		}
		borrar_bloque(pointer, data);
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
}