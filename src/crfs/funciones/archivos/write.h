#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "../generales/bitmap.h"
#include "../../estructuras.h"
#include "../utils.h"


int cr_write(crFILE* file_desc, void* buffer, int nbytes);
//int bitmap_value(unsigned int pointer, FILE* data);
//int condition(FILE* data);
unsigned int bit_pointer(FILE *data);
unsigned int index_pointer(FILE* data, crFILE* file_desc);
unsigned int index_indirecto(FILE* data, crFILE* file_desc, unsigned int index_file);
void setear_indirecto(FILE* data, crFILE* file_desc, unsigned int index_file);
