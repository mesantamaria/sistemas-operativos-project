#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../../estructuras.h"
#include "../globals.h"
#include "read.h"

int cr_read(crFILE* file_desc, void* buffer, int nbytes) {
	FILE* data = fopen(disk_path, "rb");
	unsigned char *buffer2 = malloc(sizeof(unsigned char) * 2048);
	unsigned char *buffer_bloque_indirecto = malloc(sizeof(unsigned char) * 2048);

	fseek(data, (file_desc -> pointer) + file_desc -> bytes_leidos, SEEK_SET);
	int bytes_por_leer = nbytes;
	int block = file_desc -> bytes_leidos / 2048;
	bool indirect_block = false;
	int byte_in_block = file_desc -> bytes_leidos % 2048;
	int posicion_buffer = 0;
	if (block >= 500)
	{	
		indirect_block = true;
		block -= 500;
	}
	if (indirect_block && (block > 10 * 2048 / 4))
	{
		printf("Se superó el espacio máximo\n");
		free(buffer2);
		free(buffer_bloque_indirecto);
		fclose(data);
		return 0;
	}
	int contador = 0;
	int indirecto = 0;
	int offset_indirecto = 0;
	int puntero;
	while(contador < bytes_por_leer){
		if (block > 0 || indirect_block)
		{
			fseek(data, (file_desc -> pointer), SEEK_SET);
			if (!indirect_block)
			{
				fread(buffer2, sizeof(unsigned char), 2048, data);
				puntero = ((unsigned int)buffer2[8 + block*4] * 256 * 256 * 256 + 
				(unsigned int)buffer2[9 + block*4] * 256 * 256 + 
				(unsigned int)buffer2[10 + block*4] * 256 + (unsigned int)buffer2[11 + block*4]) * 2048;
				fseek(data, puntero, SEEK_SET);
			}
			else
			{	// caso bloque indirecto, doble direccionamiento
				if (block > 10 * 2048 / 4)
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
				offset_indirecto = (2048 / 4) % block;
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
			if (block >= 500)
			{
				indirect_block = true;
				block -= 500;
			}
		}
	}


	file_desc -> bytes_leidos += contador;
	free(buffer2);
	free(buffer_bloque_indirecto);
	fclose(data);
	return contador;
	
}