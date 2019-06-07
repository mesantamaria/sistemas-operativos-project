
#pragma once

typedef struct Package
{
	int ID;
	int payload_size;
	char* payload;
} Package;

Package* package_init(int ID, int payload_size);
void free_package(Package* package);

