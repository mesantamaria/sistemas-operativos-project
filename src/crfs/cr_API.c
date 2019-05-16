#include <stdlib.h>
#include <stdio.h>
#include "cr_API.h"


int read_entry ( unsigned char *buffer ) {
	if ( buffer[0] == (unsigned char)1 ) {
		return 0;
	} else {
		if ( buffer[0] == (unsigned char)2 ) {
			printf( "DIR %s index: %u\n", buffer + 1, (unsigned int)buffer[30] * 256 + (unsigned int)buffer[31] );  // usa el 30 y el 31 porque los 2 Byte más significativos no se usan
		} else {
			printf( "FILE %s index: %u\n", buffer + 1, (unsigned int)buffer[30] * 256 + (unsigned int)buffer[31] );
		};
		return 0;
	};
};
