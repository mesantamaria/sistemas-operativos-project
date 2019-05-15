#include <stdlib.h>
#include <stdio.h>
#include "mount.h"
#include "../globals.h"

void cr_mount(char* diskname) {
	disk_path = diskname;
}
