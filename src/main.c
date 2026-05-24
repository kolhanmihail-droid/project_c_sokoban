#include <stdio.h>
#include <stdlib.h>
#include "../include/logika_gry.h"

int main(int argc, char *argv[]) {
    printf("Witaj w projekcie Sokoban!\n");
    
    // Tworzymy nasza strukture
    GameState game;
    
    // Inicjalizujemy gre - np. mapa 10 na 10
    initGame(&game, 10, 10);

    // ... (W przyszlosci tutaj bedzie kod wczytujacy mape z pliku) ...

    // Koniec gry, sprzatamy zeby nie bylo wyciekow pamieci!
    freeGame(&game);

    printf("Koniec programu.\n");
    return 0;
}