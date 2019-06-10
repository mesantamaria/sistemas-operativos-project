#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wchar.h>
#include <locale.h>
#include "math.h"
#include "util.h"


Package* receiveMessage(int socket){
    printf("Waiting message... \n");
    // Esperamos a que llegue el primer byte, que corresponde al ID del paquete
    char ID;
    recv(socket, &ID, 1, 0);
    printf("\n####### Paquete recibido ####\n");
    printf("The ID is: %d\n", ID); // lo imprimimos como número porque esa es la interpretación que acordamos

    // Recibimos el payload size en el siguiente byte
    char payloadSize;
    recv(socket, &payloadSize, 1, 0);
    printf("The PayloadSize is: %d\n", payloadSize);
    Package* package = package_init(ID, payloadSize);
    // Recibimos el resto del paquete, según el payloadSize. Lo guardamos en un puntero de caracteres, porque no es necesario modificarlo
    //package -> payload = malloc(payloadSize);
    if (!payloadSize)
    {
        //printf("Servidor envió paquete de Connection Established\n");
    }
    else{
        recv(socket, package -> payload, payloadSize, 0);
        package -> payload[payloadSize] = '\0';
        printf("The Message is: %s\n", package -> payload);
    }
    printf("#############################\n");

    // Aqui se las ingenian para ver como retornan todo. Puden retornar el paquete y separarlo afuera, o retornar una struct.
    return package;
}

void sendMessage(int socket, char* package){
    // Obtenemos el largo del payload para saber qué tamaño tiene el paquete y cuántos bytes debe enviar mi socket
    int payloadSize = package[1];
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

void print_tablero(char* buffer, int ID){
    int i, j, j_real;
    char* letras = "ABCDEFGH";
    printf("   ");
    for (j = 0; j < 8; j++) {
        if (ID == 2) {
            j_real = 7 - j;
        }
        else j_real = j;
        printf("| %c ", letras[j_real]);
    }
    printf("|\n---");
    for (j = 0; j < 8; j++) {
        printf("+---");
    }
    printf("+---\n");
    i = 0;
    for (int counter = 0; counter < 8; counter++) {
        if (ID == 2)
        {
            i = 7 - counter;
        }
        else i = counter;
        printf(" %d ", i+1);
        for (j = 0; j < 8; j++) {
            if (ID == 2) {
                j_real = 7 - j;
            }
            else j_real = j;
            printf("| %c ", to_unicode(buffer[j_real +  8*i]));
        }
        printf("| %d \n---", i+1);
        for (j = 0; j < 8; j++) {
            printf("+---");
        }
        printf("+---\n");
    }
    printf("   ");
    for (j = 0; j < 8; j++) {
        if (ID == 2) {
            j_real = 7 - j;
        }
        else j_real = j;
        printf("| %c ", letras[j_real]);
    }
    printf("|\n\n");
}

char to_unicode(char estado) {
    switch(estado) {
        case 'b': return ' ';
        case 'n': return ' ';
        case 'o': return 'o';
        case 'O': return 'O';
        case 'x': return 'x';
        case 'X': return 'X';
        default: return ' ';
    }
}
