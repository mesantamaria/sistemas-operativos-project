#pragma once

typedef struct crFILE
{
	unsigned int pointer;
	char mode;
	int bytes_leidos;
} crFILE;

crFILE* crFILE_init(unsigned int pointer, char mode);