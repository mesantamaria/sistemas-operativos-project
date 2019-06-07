#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../estructuras_compartidas.h"
#include "return_nickname.h"

void return_nickname(char *nickname){
  char size = strlen(nickname) + 1;
  Package *package = package_init(4, size);
  package->payload = nickname;
  send_package(package,"s");
};
