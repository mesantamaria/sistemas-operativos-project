#pragma once

typedef struct Package
{
  char id;
  char size;
  char *payload;

}Package;

Package* package_init(char id, char size);
void send_package(Package *package, char *tipo);
