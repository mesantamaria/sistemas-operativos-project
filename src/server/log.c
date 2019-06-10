#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "log.h"
#include "estructuras.h"

int LOG;

void log_event(Package* package) {
	if (LOG) {
		FILE *f = fopen("log.txt", "a");
		time_t ltime; /* calendar time */
    	ltime=time(NULL); /* get current cal time */
    	char* timestamp = asctime(localtime(&ltime));
    	timestamp[strlen(timestamp) - 1] = 0;
    	if (package -> ID != -1) {
	    	char * nombre_paquete = get_package_name(package -> ID);
	    	if (package -> payload_size > 0) {
				fprintf(f, "%s: %s - ", timestamp, nombre_paquete);
				fprintf(f, "Payload Size: %d - Content: ", package -> payload_size);
				char ID = package -> ID;
				if (ID == 3 || ID == 4 || ID == 5 || ID == 9 || ID == 10 || ID == 19 || ID == 20) {
					fprintf(f, "%s\n", package -> payload);
				}
				else {
					for (int i = 0; i < package -> payload_size; i++) {
						fprintf(f, "%d", package -> payload[i]);
					}
					fprintf(f, "\n");
				}
			}
			else {
				fprintf(f, "%s: %s\n", timestamp, nombre_paquete);
			}
		}
		else {
			fprintf(f, "----------------------------------------------------------------------------\n");
			fprintf(f, "%s: INICIO SERVIDOR\n", timestamp);
		}
		fclose(f);
	}
}

char * get_package_name(char ID) {
	switch(ID) {
		case 1: return "Start Connection";
		case 2: return "Connection Established";
		case 3: return "Ask Nickname";
		case 4: return "Return Nickname";
		case 5: return "Oponent found";
		case 6: return "Start Game";
		case 7: return "Scores";
		case 8: return "Who's First";
		case 9: return "BoardState";
		case 10: return "Send Move";
		case 11: return "Error Move";
		case 12: return "OK Move";
		case 13: return "End Game";
		case 14: return "Game Winner/Losser";
		case 15: return "Ask New Game";
		case 16: return "Answer New Game";
		case 17: return "Disconnect";
		case 18: return "Error Bad Package";
		case 19: return "Send Message";
		case 20: return "Spread Message";
		case 64: return "Image";
	}
}