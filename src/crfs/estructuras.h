#pragma once

typedef struct crFILE
{
	unsigned int pointer;
	char mode;
} crFILE;

crFILE* crFILE_init(unsigned int pointer, char mode);