#include <stdlib.h>
#include <stdio.h>
#include "estructuras_compartidas.h"

Package* package_init(char id, char size)
{
  Package *package = malloc(sizeof(Package));

  package->id = id;
  package->size = size;
  package->payload = malloc(size*sizeof(char));

  return package;
};

void send_package(Package *p ,char *tipo){

  Package *package = p;

  //enviar paquete
  if(!(package->id == 1)){
    free(package->payload);
  }
  free(package);
};
