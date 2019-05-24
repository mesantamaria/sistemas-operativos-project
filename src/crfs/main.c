#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "estructuras.h"
#include "cr_API.h"
#include "funciones/generales/mount.h"
#include "funciones/generales/ls.h"
#include "funciones/generales/exists.h"
#include "funciones/generales/bitmap.h"
#include "funciones/generales/mkdir.h"
#include "funciones/archivos/open.h"
#include "funciones/archivos/close.h"
#include "funciones/archivos/hardlink.h"
#include "funciones/archivos/rm.h"
#include "funciones/utils.h"
#include "funciones/archivos/read.h"
#include "funciones/archivos/unload.h"
#include "funciones/archivos/write.h"




int main(int argc, char *argv[])
{
	if (argc < 2)
	{
	    printf("Modo de uso: ./crfs <disk>]\n");
	    return 0;
	}

	// Obtenemos el nombre del archivo del disco.
	int mode = atoi(argv[2]);
	char* disk = argv[1];

	printf("Monto el disco %s\n", disk);
	cr_mount(disk);
	//cr_ls("memes");
	//printf("Bitmap:\n");

	//cr_ls("memes");
	// cr_bitmap();  // Imprime el bitmap

	//cr_ls("memes");



	if (mode == 3)
	{
		cr_ls("");
		printf("------- rm -------\n");
		//cr_bitmap();
		printf("Exists file: %i\n", cr_exists("/Program in C.mkv"));
		cr_rm("/Program in C.mkv");
		cr_bitmap();
		printf("Exists file: %i\n", cr_exists("/Program in C.mkv"));
	}
	else if (mode == 4)
	{

		crFILE* cr_file = cr_open("/germy.txt", 'r');
		unsigned char *buffer2 = malloc(sizeof(unsigned char) * 2048 * 9 );
		int a = cr_read(cr_file, buffer2, 2300);
		int b = cr_read(cr_file, buffer2, 24);
		printf("%d %d\n", a, b);
		//fread(buffer2, sizeof(unsigned char), 2048, data);
		//printf("%d\n", (unsigned int)buffer2[8] * 256 * 256 * 256 + (unsigned int)buffer2[9] * 256 * 256 + (unsigned int)buffer2[10] * 256 + (unsigned int)buffer2[11]);
		//int a = cr_read(cr_file, buffer2, 2048);
		//int b = cr_read(cr_file, &buffer2[2048], 2048);
		//printf("%d %d\n", a, b);
		//printf("%d\n", (unsigned int)buffer2[0] * 256 * 256 * 256 + (unsigned int)buffer2[1] * 256 * 256 + (unsigned int)buffer2[2] * 256 + (unsigned int)buffer2[3]);
		free(buffer2);
		free(cr_file);
		//cr_ls("memes");
		//unload_file("/memes/cmake.png", "cmake.png");
		//cr_unload("/SSBS.mp3", "cancion.mp3");
		//cr_unload("/memes", "descargas");
		//cr_unload("/germy.txt", "germy.txt");
		//cr_unload("/Program in C.mkv", "Program in C.mkv");
		//cr_unload("/free.jpg", "free.jpg");

	}
	else if (mode == 1)
	{
		printf("------- memes -------\n");
		cr_ls("/memes");
		printf("\nAbro el ya existente 'for.jpg' en modo 'r'\n");
		crFILE* cr_file = cr_open("/memes/for.jpg", 'r');
		printf("------- memes -------\n");
		cr_ls("/memes");
		printf("\nAbro el no existente 'fortress.jpg' en modo 'w'\n");
		crFILE* cr_file_1 = cr_open("/memes/fortress.jpg", 'w');
		printf("------- memes -------\n");
		cr_ls("/memes");
		printf("\nCreo directorio pizza en memes\n");
		cr_mkdir("/memes/pizza");
		printf("------- memes -------\n");
		cr_ls("/memes");
		printf("\nCreo nuevamente directorio pizza en memes\n");
		cr_mkdir("/memes/pizza");
		printf("------- memes -------\n");
		cr_ls("/memes");
		printf("\nAbro en /memes/pizza el no existente 'gol.txt' en modo 'w'\n");
		crFILE* cr_file_2 = cr_open("/memes/pizza/gol.txt", 'w');
		printf("------- memes/pizza -------\n");
		cr_ls("/memes/pizza");
		printf("\nBorro gol.txt\n");
		cr_rm("/memes/pizza/gol.txt");
		printf("------- memes/pizza ------- \n");
		cr_ls("/memes/pizza");
		printf("\nCreo nuevamente gol.txt\n");
		crFILE* cr_file_3 = cr_open("/memes/pizza/gol.txt", 'w');
		printf("------- memes/pizza -------\n");
		cr_ls("/memes/pizza");
		printf("\nIntento crear nuevamente gol.txt\n");
		crFILE* cr_file_4 = cr_open("/memes/pizza/gol.txt", 'w');
		printf("\nCreo un hardlink de '/memes/fortress.jpg' en '/memes/pizza'\n");
		cr_hardlink("/memes/fortress.jpg", "/memes/pizza");
		printf("------- memes/pizza -------\n");
		cr_ls("/memes/pizza");
		printf("\nIntento abrir en modo 'r' un archivo no existente\n");
		crFILE* cr_file_5 = cr_open("/memes/pizza/no_esta.jpg", 'r');
		printf("\nIntento abrir en modo 'w' un archivo existente\n");
		crFILE* cr_file_6 = cr_open("/memes/pizza/gol.txt", 'w');
		printf("\nIntento abrir un archivo de una ruta que no existe\n");
		crFILE* cr_file_7 = cr_open("/memes/picza/gol.txt", 'r');
		printf("\nIntento crear un hardlink de '/memecillos/fortress.jpg' en '/memes/pizza'\n");
		cr_hardlink("/memecillos/fortress.jpg", "/memes/pizza");
		printf("\nIntento crear un hardlink de '/memes/fortress.jpg' en '/memecillos/pizza'\n");
		cr_hardlink("/memes/fortress.jpg", "/memecillos/pizza");
		printf("\nIntento crear un hardlink de '/memes/monos.jpg' en '/memes/pizza'\n");
		cr_hardlink("/memes/monos.jpg", "/memes/pizza");
		printf("\nIntento crear un hardlink de '/memes/fortress.jpg' en '/memes/pizza'\n");
		cr_hardlink("/memes/fortress.jpg", "/memes/pizza");




		cr_close(cr_file);
		cr_close(cr_file_1);
		cr_close(cr_file_2);
		cr_close(cr_file_3);
		cr_close(cr_file_4);
		cr_close(cr_file_5);
		cr_close(cr_file_6);
		cr_close(cr_file_7);
	}else if (mode ==2){
		//crFILE* cr_file = cr_open("/memes/drake.jpeg", 'w');

		/*crFILE* cr_file = cr_open("prueba0.txt", 'w');
>>>>>>> fix

		FILE* data0 = fopen("prueba0.txt", "rb");

		unsigned char *buffer = malloc(sizeof(unsigned char) * 1000);
		for(int i=0;i<1000;i++){
			unsigned char aux;

			fscanf(data0, "%c", &aux);
			buffer[i]=aux;
		}

		cr_write(cr_file, buffer, 1000);

		cr_read(cr_file, buffer, 1000);

		for(int i=0;i<1000; i++){
			printf("%c", buffer[i]);
		}

		free(buffer);
		*/


	}
	else if (mode == 5)
	{
		printf("\nAbro archivo 'germy.txt' en modo 'r'\n");
		crFILE* cr_file = cr_open("/germy.txt", 'r');
		unsigned char *buffer = malloc(sizeof(unsigned char) * 2048 * 9 );
		int bytes_leidos = cr_read(cr_file, buffer, 2048);
		
		printf("\n'germy.txt' tiene un tamaño de 277 Bytes. Leo los 277 Bytes\n" );
		bytes_leidos = cr_read(cr_file, buffer, 277);  // Los 2048 son una decisión de diseño
 		printf("Se leyeron con éxito %d Bytes\n", bytes_leidos);
 		
 		printf("\nIntento leer 20 Bytes más de 'germy.txt'\n" );
 		bytes_leidos = cr_read(cr_file, buffer, 20);
 		printf("Se leyeron con éxito %d Bytes\n", bytes_leidos);

 		printf("\nCierro el archivo 'germy.txt'\n");
 		cr_close(cr_file);

 		printf("\nAbro archivo 'germy.txt' en modo 'r'\n");
		cr_file = cr_open("/germy.txt", 'r');
		
		printf("\n'germy.txt' tiene un tamaño de 277 Bytes. Intento leer 300 Bytes\n" );
		bytes_leidos = cr_read(cr_file, buffer, 2048);  // Los 2048 son una decisión de diseño
		bytes_leidos = cr_read(cr_file, buffer, 300);
 		printf("Se leyeron con éxito %d Bytes\n", bytes_leidos);

		printf("\nCierro el archivo 'germy.txt'\n");
 		cr_close(cr_file); 		

		printf("\nMe gusta thanos así que reviso si existe una carpeta que se llame así con 'cr_exists'\n");
		if (cr_exists("/thanos"))
		{
			printf("La carpeta existe\n");
		}
		else printf("La carpeta no existe\n");

		printf("\nCopio la carpeta 'thanos' a mi computador para tener todo sobre él. Lo voy a copiar en una carpeta llamada 'Descargas'\n");
		cr_unload("/thanos", "Descargas");

		printf("\nTambién me gusta 'Iron Man' así que voy a intentar copiar su contenido también en mi computador\n");
		cr_unload("/Iron Man", "Descargas");

		printf("\nVeo que hay un video en el disco sobre C. Lo copio a mi carpeta de Descargas para verlo\n");
		cr_unload("/Program in C.mkv", "Descargas");




 		

		free(buffer);
		//cr_close(cr_file);

	}
	return 0;
}
