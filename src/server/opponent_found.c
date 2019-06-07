#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "opponent_found.h"

void opponent_found(char *nickname, char *tipo){
  char size = strlen(nickname) + 1;
  Package *package = package_init(5, size);
  package->payload = nickname;
  //send_package(package, tipo);
};
