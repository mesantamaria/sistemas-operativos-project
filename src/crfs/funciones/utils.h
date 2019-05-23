#pragma once

void* get_pointer_from_path(char* path, FILE* data);
void change_bitmap(unsigned int bloque, int value, FILE* data);
unsigned int get_pointer(unsigned int entry, FILE* data);