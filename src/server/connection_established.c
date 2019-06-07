#include <stdlib.h>
#include <stdio.h>
#include "../estructuras_compartidas.h"
#include "connection_established.h"

void connection_established(char *tipo){
  Package *package = package_init(2, 0);
  send_package(package, tipo);
};
