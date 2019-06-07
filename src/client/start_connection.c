#include <stdlib.h>
#include <stdio.h>
#include "../estructuras_compartidas.h"
#include "start_connection.h"

void start_connection(){
  Package *package = package_init(1, 0);
  send_package(package,"s");
}
