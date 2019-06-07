#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "scores.h"

void scores(char score1, char score2 , char *tipo){

  Package *package = package_init(7, 2);

  package ->payload[0] = score1;
  package ->payload[1] = score2;
  /*
  if(!strcmp("b",tipo))
    send_package(package, "b");
  else if(!strcmp("n",tipo)){
    send_package(package, "n");
  }
  */

};
