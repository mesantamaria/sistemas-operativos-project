#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructuras.h"
#include "util.h"
#include "scores.h"

//void scores(int socket, char score_jugador, char score_contrincante){
void scores(Client** clients){
    char package[4];
    package[0] = 7;
    package[1] = 2;
    int index = 1;
    for (int i = 0; i < 2; ++i)
    {
        package[2] = (char) clients[i] -> puntaje;
        package[3] = (char) clients[index] -> puntaje;
        sendMessage(clients[i] -> socket, package);
        index--;
    }
};
