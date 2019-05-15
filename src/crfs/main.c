#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/timeb.h>
#include <pthread.h>
#include "files.h"
#include "map.h"
#include "reduce.h"
#include "mapreduce.h"
#include "estructuras.h"
#include "others.h"



int main(int argc, char *argv[])
{
	if (argc < 2)
	{
	    printf("Modo de uso: ./crfs <disk>]\n");
	    return 0;
	}

	// Obtenemos el nombre del archivo del disco.
	char* disk = argv[1];

	// Destruimos todo

	return 0;
}
