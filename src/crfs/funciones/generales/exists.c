#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../globals.h"
#include "exists.h"

int cr_exists(char* path) {
	if (strcmp(path, "") == 0)
	{
		return 1;
	}
	FILE* data = fopen(disk_path, "rb" );
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 32);
	char copy[strlen(path)];
	strcpy(copy, path);
	unsigned int pointer = 0;
	char* folder = strtok(copy, "/");
	bool found = false;
	while(folder != NULL){
		found = false;
		for(int i = 0; i < 64; i++) {  // 2048 / 32  = 64
			fseek(data, 32 * i + pointer, SEEK_SET);
			fread(buffer, sizeof(unsigned char), 32, data);
			if (buffer[0] != (unsigned char)1 && strcmp(folder, (const char*) (buffer + 1)) == 0 )
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
			return 0;
		}
		folder = strtok(NULL, "/");
	}

	free(buffer);
	fclose(data);
	return 1;
}