#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../globals.h"
#include "ls.h"

void cr_ls(char* path) {
	FILE* data = fopen(disk_path, "rb" );
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 32);

	if (strcmp(path, "") == 0)
	{
		for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
			fseek(data, 32 * i, SEEK_SET);
			fread(buffer, sizeof(unsigned char), 32, data);
			if (buffer[0] != (unsigned char)1)
			{
				printf("%s\n", buffer + 1);
			}
		};
	}
	//printf("%s\n", buffer + 1);
	//fseek(data, ((unsigned int)buffer[30] * 256 + (unsigned int)buffer[31]) * 2048, SEEK_SET);
	//fread(buffer, sizeof(unsigned char), 32, data);
	//printf("%s\n", buffer + 1);
	free(buffer);
	fclose(data);
}