#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../globals.h"
#include "ls.h"


void cr_ls(char* path) {
	FILE* data = fopen(disk_path, "rb" );
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 32);
	char copy[28];
	strcpy(copy, path);
	unsigned int pointer = 0;
	char* folder = strtok(copy, "/");
	while(strcmp(path, "") != 0 && folder != NULL){
		printf("FOLDER: %s\n", folder);
		for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
			fseek(data, 32 * i + pointer, SEEK_SET);
			fread(buffer, sizeof(unsigned char), 32, data);
			if (buffer[0] != (unsigned char)1 && strcmp(folder, (const char*) (buffer + 1)) == 0 )
			{
				pointer = ((unsigned int)buffer[30] * 256 + (unsigned int)buffer[31]) * 2048;
				break;
			}
		}
		folder = strtok(NULL, "/");
	}
	for(int i = 0; i < 64; i++) {
		fseek(data, 32 * i + pointer, SEEK_SET);
		fread(buffer, sizeof(unsigned char), 32, data);
		if (buffer[0] != (unsigned char)1)
		{
			printf("%s\n", buffer + 1);
		}
	};

	free(buffer);
	fclose(data);
}