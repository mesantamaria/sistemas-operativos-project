#include <stdlib.h>
#include <stdio.h>
#include "estructuras.h"

crFILE* crFILE_init(unsigned int pointer, char mode)
{
	crFILE* cr_file = malloc(sizeof(crFILE));

	cr_file -> pointer = pointer;
	cr_file -> mode = mode;
	cr_file -> bytes_leidos = 0;

	return cr_file;
}