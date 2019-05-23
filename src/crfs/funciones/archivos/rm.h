#pragma once

int cr_rm(char* path);


void borrar_bloques_punteros_indirectos(unsigned int punteros, unsigned int  n_punteros, FILE* data);
void borrar_bloques_punteros(unsigned int punteros, unsigned int  n_punteros, FILE* data);
void borrar_bloque(unsigned int pointer, FILE* data);
void borrar_puntero_directorio(char* path, FILE* data);