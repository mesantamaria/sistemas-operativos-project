#include <stdlib.h>
#include <stdio.h>
#include "../../estructuras.h"
#include "../globals.h"

int cr_close(crFILE* file_desc) {
	if (file_desc != NULL)
	{
		free(file_desc);
		return 1;
	}
	return 0;
}