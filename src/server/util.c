#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "math.h"
#include "util.h"
#include "log.h"
#include "estructuras.h"
#include "error_bad_package.h"


Package* receiveMessage(int socket){
    printf("Waiting message... \n");
    // Esperamos a que llegue el primer byte, que corresponde al ID del paquete
    char ID;
    recv(socket, &ID, 1, 0);
    printf("\n####### Paquete recibido ####\n");
    printf("The ID is: %d\n", ID); // lo imprimimos como número porque esa es la interpretación que acordamos

    int contador_id = 0;

    for(int i=1;i<21;i++)
    {
      if(ID==i)
      {
        contador_id++;
        break;
      }
    }
    if(ID==64)
    {
      contador_id++;
    }
    if(contador_id==0)
    {
      error_bad_package(socket);
    }

    // Recibimos el payload size en el siguiente byte
    char payloadSize;
    recv(socket, &payloadSize, 1, 0);
    printf("The PayloadSize is: %d\n", payloadSize);
    Package* package = package_init(ID, payloadSize);
    // Recibimos el resto del paquete, según el payloadSize. Lo guardamos en un puntero de caracteres, porque no es necesario modificarlo
    //package -> payload = malloc(payloadSize);
    if((ID==1 || ID==2 || ID==3 || ID==6 || ID==11||ID==12||ID==13||ID==15||ID==17||ID==18) && !(payloadSize==0))
    {
      error_bad_package(socket);

    }
    else if(ID==7 && !(payloadSize==2))
    {
      error_bad_package(socket);

    }
    else if(ID==8 && !(payloadSize==1))
    {
      error_bad_package(socket);

    }
    else if(ID==9 && !(payloadSize==64))
    {
      error_bad_package(socket);

    }
    else if(ID==10 && !(payloadSize==4))
    {
      error_bad_package(socket);

    }
    else if(ID==14 && !(payloadSize==1))
    {
      error_bad_package(socket);

    }
    else if(ID==16 && !(payloadSize==1))
    {
      error_bad_package(socket);
    }

    if (!payloadSize)
    {
        //printf("Cliente %d envió paquete de Start Connection\n", socket);;
    }
    else
    {
        recv(socket, package -> payload, payloadSize, 0);
        package -> payload[payloadSize] = '\0';
        printf("The Message is: %s\n", package -> payload);
    }
    // Logueamos
    log_event(package);
    printf("#############################\n");


    // Aqui se las ingenian para ver como retornan todo. Puden retornar el paquete y separarlo afuera, o retornar una struct.
    return package;
}

void sendMessage(int socket, char* package){
    // Obtenemos el largo del payload para saber qué tamaño tiene el paquete y cuántos bytes debe enviar mi socket
    int payloadSize = package[1];
    // Logueamos
    Package* p = package_init(package[0], package[1]);
    strcpy(p -> payload, package + 2);
    log_event(p);
<<<<<<< HEAD
=======
    free(p -> payload);
    free(p);
    // Obtenemos el largo del payload para saber qué tamaño tiene el paquete y cuántos bytes debe enviar mi socket
    int payloadSize = package[1];
>>>>>>> bb6f0d630aba7c548985236f99a752bb5de2a3d8
    send(socket, package, 2 + payloadSize, 0);
}

int calculate_length(char * input){
    int i = 0;
    while (1){
        if (input[i] == '\0'){
            return i;
        }
        i++;
    }
}

void print_package(char * package){
    // Los primeros dos bytes los imprimimos como 'd' (números), porque así acordamos interpretarlos.
    printf("   Paquete es: ");
    printf("%d ", package[0]); printf("%d ", package[1]); printf("%s\n", &package[2]);

    /*
    // No hay diferencia entre un char o un int en la forma en que se guardan en memoria -> '01001110'
    // La diferencia es lo que representa, osea cómo yo lo interpreto y uso (letra o entero)
    for (int i=0; i<5; i++){
        // Si imprimimos cada caracter del mensaje como un numero, vemos su código ascii
        printf("%d ", package[2+i]);
    }
    printf("\n");
    */
}
