#include <unistd.h>  
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "init_server.h"
#include "damas/tablero.h"
#include "damas/utils.h"
#include "damas/jugadas.h"
#include "estructuras.h"




int main(int argc, char *argv[])
{
	if (argc < 5)
	{
	    printf("Modo de uso: ./server -i <ip_address> -p <tcp-port> -l\n");
		Tablero* tablero = tablero_init();
		print_tablero(tablero);
		jugar(tablero, 5, 1, 4, 2);
		jugar(tablero, 2, 0, 3, 1);
		jugar(tablero, 4, 2, 2, 0);
		destroy_tablero(tablero);
	    return 1;
	}

	int opt;
	char* IP;
	int PORT;  
    while((opt = getopt(argc, argv, "i:p:l")) != -1)  
    {  
        switch(opt)  
        {  
            case 'i':
            	IP = optarg;
            	break;
            case 'p':
            	PORT = atoi(optarg);
            	break;
            case 'l':
            	printf("True\n");  
            	break;
        }  
    }  
    
	printf("I'm the Server\n");
	//char* IP = argv[2];
	//int PORT = atoi(argv[4]);
	printf("%s %d\n", IP, PORT);



	Client** clients = initializeServer(IP, PORT);
	for (int i = 0; i < 2; ++i)
	{
		free_client(clients[i]);
	}
	free(clients);


	//while(true)
	//{

	//}


	return 0;
}
