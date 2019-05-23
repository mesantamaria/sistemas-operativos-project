#include <stdlib.h>
#include <stdio.h>
#include "../globals.h"
#include "bitmap.h"


int int_to_bits(unsigned int value){  // Size of integer is 8 bits = 1 Byte
	// Retorna cantidad de '1's en número binario
	int cantidad = 0;
	int k;
	for (int c = 7; c >= 0; c--)
	{
		k = value >> c;
		printf("%d\n", k);
		if (k & 1){
			cantidad ++;
			//printf("1");
			//fprintf(stderr, "1");  // Hacerlo con printf se ejecuta más rápido
		}
		else{
			//printf("0");
			//fprintf(stderr, "0");
		}
	}
	return cantidad;
}


void cr_bitmap() {
	FILE* data = fopen(disk_path, "rb" );
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 8192);  // 2048 * 4 = 8192
	fseek(data, 2048, SEEK_SET);  // Bloques de Bitmap parten desde Bloque 1
	fread(buffer, sizeof(unsigned char), 8192, data);  // Bloques de Bitmap desde Bloque 1 al 4
	printf("%d\n", (unsigned int)buffer[0]);
	int bloques_ocupados = 0;
	for (int i = 0; i < 8192; ++i)
	{
		bloques_ocupados += int_to_bits((unsigned int)buffer[i]);
	}
	printf("\n%d\n%d\n", bloques_ocupados, total_blocks - bloques_ocupados);  // Hay 65536 Bloques en disco
	free(buffer);
	fclose(data);
}
