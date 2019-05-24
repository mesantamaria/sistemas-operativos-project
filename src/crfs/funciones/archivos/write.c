
#include <stdlib.h>
#include <stdio.h>
#include "../generales/bitmap.h"
#include "../../estructuras.h"
#include "../utils.h"
#include "../globals.h"
#include "write.h"

/*
int bitmap_value(unsigned int pointer, FILE* data){

  unsigned int bitmap_bit = pointer/2048 + 2048;

  unsigned int bit_row = bitmap_bit/8;

  unsigned int bit_col = bitmap_bit%8;

  unsigned int bit;

  fseek(data,bitmap_bit,SEEK_SET);
  //fread(,1,1,data)

  for (int c = 0; c < 8 ; c++)
  {
    if(c==bit_col){
      bit = bit_row;
    }
  }
  return bit;
}

int condition(FILE* data){
  data = fopen(disk_path, "rb" );
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 8192);  // 2048 * 4 = 8192
	fseek(data, 2048, SEEK_SET);  // Bloques de Bitmap parten desde Bloque 1
	fread(buffer, sizeof(unsigned char), 8192, data);  // Bloques de Bitmap desde Bloque 1 al 4
	int bloques_ocupados = 0;
	for (int i = 0; i < 8192; ++i)
	{
		bloques_ocupados += int_to_bits((unsigned int)buffer[i]);
	}
	free(buffer);
	fclose(data);

  if(bloques_ocupados<total_blocks){
    return 1;
  }else{
    return 0;
  }

}

*/
/* bit_pointer retorna el index del primer bitmap en 0 encontrado, si no se encuentra nada se retorna 0 */
unsigned int bit_pointer(FILE *data){

  //data = fopen(disk_path, "rb" );
	unsigned char *buffer = malloc(sizeof( unsigned char ) * 8192);  // 2048 * 4 = 8192
	fseek(data, 2048, SEEK_SET);  // Bloques de Bitmap parten desde Bloque 1
	fread(buffer, sizeof(unsigned char), 8192, data);  // Bloques de Bitmap desde Bloque 1 al 4
  unsigned int num = 0;
	for (int i = 0; i < 8192; ++i)
	{
		if(!int_to_bits((unsigned int)buffer[i])){
      num = i;
      break;
    }
	}
	free(buffer);
	//fclose(data);

  return num;
}

/* index_pointer retorna el primer indice del bloque indice si es que se encuentran 4 bytes en 0 seguidos*/
unsigned int index_pointer(FILE* data, crFILE* file_desc){
  //data = fopen(disk_path, "rb" );
  unsigned char *buffer = malloc(sizeof( unsigned char ) * 2048);  // 2048 * 4 = 8192
  fseek(data, file_desc->pointer * 2048, SEEK_SET);
  fread(buffer, sizeof(unsigned char), 2048, data);
  unsigned int index = 0;
  for (int i = 8; i < 2044;)
  {
    if((unsigned int)buffer[i]==0 && (unsigned int)buffer[i+1]==0 &&
     (unsigned int)buffer[i+2]==0 && (unsigned int)buffer[i+3]==0){
       index = i;
      break;
    }
    i = i+4;
  }

  free(buffer);
  //fclose(data);

  return index;

}


void setear_indirecto(FILE* data, crFILE* file_desc, unsigned int index_file){

  unsigned char *buffer = malloc(sizeof( unsigned char ) * 2048);  // 2048 * 4 = 8192
  fseek(data, index_file*2048, SEEK_SET);  // Bloques de Bitmap parten desde Bloque 1
  fread(buffer, sizeof(unsigned char), 2048, data);  // Bloques de Bitmap desde Bloque 1 al 4
  unsigned int index = 0;
  for (int i = 0; i < 2048;){
    buffer[i]=0;
    i = i+4;
  }

  free(buffer);
}

/*index_indirecto retorna el index de */
unsigned int index_indirecto(FILE* data, crFILE* file_desc, unsigned int index_file){
  //data = fopen(disk_path, "rb" );
  unsigned char *buffer = malloc(sizeof( unsigned char ) * 2048);  // 2048 * 4 = 8192
  unsigned int pointer_to_data = get_pointer(file_desc->pointer*2048 + index_file, data);
  fseek(data, pointer_to_data, SEEK_SET);  // Bloques de Bitmap parten desde Bloque 1
  fread(buffer, sizeof(unsigned char), 2048, data);  // Bloques de Bitmap desde Bloque 1 al 4
  unsigned int index = 0;
  for (int i = 0; i < 2048;)
  {
    if((unsigned int)buffer[i]==0 && (unsigned int)buffer[i+1]==0 &&
     (unsigned int)buffer[i+2]==0 && (unsigned int)buffer[i+3]==0){
       index =i;
      break;
    }
    i = i+4;
  }

  free(buffer);
  //fclose(data);

  return index;

}


int cr_write(crFILE* file_desc, void* buffer, int nbytes){

  FILE* data = fopen(disk_path, "r+" );

  fseek(data, file_desc->pointer*2048 ,SEEK_SET);

  int cantidad_bytes = 0;

  int bytes_restantes = nbytes;

  int posicion_buffer = 0;

  if(nbytes<=2048 ){
    unsigned int indice_bitmap = bit_pointer(data); //retorna indice primer bitmap vacio
    unsigned int index_file = index_pointer(data, file_desc); //retorna indice primer puntero vacio
    if(indice_bitmap && index_file){
      //unsigned int point = pointer*2048;
      fseek(data, indice_bitmap*2048, SEEK_SET);
      fwrite(&buffer, sizeof(unsigned char), nbytes, data);
      bytes_restantes = 0;
      cantidad_bytes = nbytes;
      change_bitmap(indice_bitmap, 1,data);
      if(index_file<2004){
        fseek(data, file_desc->pointer*2048 + index_file, SEEK_SET);
        fwrite(&indice_bitmap, sizeof(unsigned int), 1, data);
      }else{
        //manejo indirecto
        unsigned int index_indirect = index_indirecto(data, file_desc,index_file);

        fseek(data, index_indirect*2048, SEEK_SET);
        fwrite(&indice_bitmap, sizeof(unsigned int), 1, data);


      }
      //escribir en puntero o en bloque indirecto y luego bloque de datos(actualizand bitmap)

  }else{
    return cantidad_bytes;
  }
  }else{

    while(bytes_restantes>0){

      unsigned int indice_bitmap = bit_pointer(data);
      unsigned int index_file = index_pointer(data, file_desc); //retorna indice primer puntero vacio

      fseek(data, indice_bitmap*2048, SEEK_SET);

      if(indice_bitmap && index_file){

        if(bytes_restantes<2048){

          fwrite(&buffer[posicion_buffer], sizeof(unsigned char), bytes_restantes, data);
          bytes_restantes = 0;
          cantidad_bytes = nbytes;

        }else{
          fwrite(&buffer[posicion_buffer], sizeof(unsigned char), 2048, data);
          bytes_restantes = bytes_restantes - 2048;
          cantidad_bytes = cantidad_bytes + 2048;
          posicion_buffer = posicion_buffer + 2048;
          //buffer = buffer + 2048;

        }
      }else{
        return cantidad_bytes;
      }
      change_bitmap(indice_bitmap, 1,data);
      if(index_file<2004){
        fseek(data, file_desc->pointer*2048 + index_file, SEEK_SET);
        fwrite(&indice_bitmap, sizeof(unsigned int), 1, data);
      }else{
        //manejo indirecto
        unsigned int index_indirect = index_indirecto(data, file_desc,index_file);

        fseek(data, index_indirect*2048, SEEK_SET);
        fwrite(&indice_bitmap, sizeof(unsigned int), 1, data);


      }
      //escribir en puntero o en bloque indirecto y luego bloque de datos(actualizand bitmap)
    }
}


  return cantidad_bytes;
}
