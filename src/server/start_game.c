#include <stdlib.h>
#include <stdio.h>
#include "../estructuras_compartidas.h"
#include "connection_established.h"

void start_game(char *tipo){
  Package *package = package_init(6, 0);
  send_package(package, tipo);
};
