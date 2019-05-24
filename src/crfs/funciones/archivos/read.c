#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../estructuras.h"
#include "../globals.h"
#include "read.h"


int file_size(crFILE* file_desc){
	FILE* data = fopen(disk_path, "rb");
	unsigned char *buffer = malloc(sizeof(unsigned char) * 4);
	fseek(data, file_desc -> pointer, SEEK_SET);
	fread(buffer, sizeof(unsigned char), 4, data);
	int tamano = (unsigned int)buffer[0] * 256 * 256 * 256 + (unsigned int)buffer[1] * 256 * 256
			+ (unsigned int)buffer[2] * 256 + (unsigned int)buffer[3];

	free(buffer);
	fclose(data);
	return tamano;
}


int cr_read(crFILE* file_desc, void* buffer, int nbytes) {
	FILE* data = fopen(disk_path, "rb");
	unsigned char *buffer2 = malloc(sizeof(unsigned char) * 2048);
	unsigned char *buffer_bloque_indirecto = malloc(sizeof(unsigned char) * 2048);
	int size = file_size(file_desc);

	fseek(data, (file_desc -> pointer) + file_desc -> bytes_leidos, SEEK_SET);
	int bytes_por_leer = nbytes;
	int block = file_desc -> bytes_leidos / 2048;
	bool indirect_block = false;
	int byte_in_block = file_desc -> bytes_leidos % 2048;
	int posicion_buffer = 0;
	
	if (nbytes > size + 2048 - file_desc -> bytes_leidos)  // Caso en que se quieren leer mas bytes de los que hay
	{
		printf("Se pide mas tamaño del que HAY\n");
		bytes_por_leer = size + 2048 - file_desc -> bytes_leidos;
		nbytes = size + 2048 - file_desc -> bytes_leidos;
	}

	if (block >= 501)  // Datos parten desde bloque 1 al 500
	{	
		indirect_block = true;
		block -= 501;
	}
	if (indirect_block && (block >= 10 * 2048 / 4))
	{
		printf("Se superó el espacio máximo\n");
		free(buffer2);
		free(buffer_bloque_indirecto);
		fclose(data);
		return 0;
	}
	int tamano = 0;
	int contador = 0;
	int indirecto = 0;
	int offset_indirecto = 0;
	int puntero;
	while(contador < bytes_por_leer){
		//printf("BLOCK %d %d %d\n", block, bytes_por_leer, byte_in_block);
		if (block > 0 || indirect_block)
		{
			fseek(data, (file_desc -> pointer), SEEK_SET);
			if (!indirect_block)
			{
				fread(buffer2, sizeof(unsigned char), 2048, data);
				puntero = ((unsigned int)buffer2[8 + (block-1)*4] * 256 * 256 * 256 + 
				(unsigned int)buffer2[9 + (block-1)*4] * 256 * 256 + 
				(unsigned int)buffer2[10 + (block-1)*4] * 256 + (unsigned int)buffer2[11 + (block-1)*4]) * 2048;
				fseek(data, puntero, SEEK_SET);
			}
			else
			{	// caso bloque indirecto, doble direccionamiento
				
				if (block >= 10 * 2048 / 4)
				{
					printf("Se superó el espacio máximo\n");
					file_desc -> bytes_leidos += contador;
					free(buffer2);
					free(buffer_bloque_indirecto);
					fclose(data);
					return contador;
				}
				fread(buffer2, sizeof(unsigned char), 2048, data);
				indirecto = block / (2048 / 4);
				puntero = ((unsigned int)buffer2[2008 + indirecto*4] * 256 * 256 * 256 + 
				(unsigned int)buffer2[2009 + indirecto*4] * 256 * 256 + 
				(unsigned int)buffer2[2010 + indirecto*4] * 256 + (unsigned int)buffer2[2011 + indirecto*4]) * 2048;
				fseek(data, puntero, SEEK_SET);
				fread(buffer_bloque_indirecto, sizeof(unsigned char), 2048, data);
				offset_indirecto = block % (2048 / 4);  // era (2048 / 4) % block
				puntero = ((unsigned int)buffer_bloque_indirecto[offset_indirecto * 4] * 256 * 256 * 256 + 
				(unsigned int)buffer_bloque_indirecto[1 + offset_indirecto *4] * 256 * 256 + 
				(unsigned int)buffer_bloque_indirecto[2 + offset_indirecto *4] * 256 + 
				(unsigned int)buffer_bloque_indirecto[3 + offset_indirecto *4]) * 2048;
				fseek(data, puntero, SEEK_SET);
			}
		}
		if (nbytes < 2048 - byte_in_block)
		{
			fread(&buffer[posicion_buffer], sizeof(unsigned char), nbytes, data);
			contador += nbytes;
		}
		else{  // pasamos a siguiente bloque
			fread(&buffer[posicion_buffer], sizeof(unsigned char), 2048 - byte_in_block, data);
			contador += 2048 - byte_in_block;
			nbytes -= 2048 - byte_in_block;
			block ++;
			byte_in_block = 0;
			posicion_buffer += 2048 - byte_in_block;
			if (block >= 501 && !indirect_block)
			{
				indirect_block = true;
				block -= 501;
			}
		}
	}

	//printf("%d\n", contador);
	file_desc -> bytes_leidos += contador;
	free(buffer2);
	free(buffer_bloque_indirecto);
	fclose(data);
	return contador;
	
}