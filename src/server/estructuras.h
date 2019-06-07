#pragma once

typedef struct Package
{
	char ID;
	char payload_size;
	char* payload;
} Package;

Package* package_init(char ID, char payload_size);
void free_package(Package* package);