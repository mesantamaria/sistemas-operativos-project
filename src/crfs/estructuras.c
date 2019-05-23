#include <stdlib.h>
#include <stdio.h>
#include "estructuras.h"

crFILE* crFILE_init(unsigned int pointer, char mode)
{
	crFILE* cr_file = malloc(sizeof(crFILE));

	cr_file -> pointer = pointer;
	cr_file -> mode = mode;

	return cr_file;
}