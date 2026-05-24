#include <stdio.h>
#include <stdlib.h>
#include "../include/logika_gry.h"
#include "../include/operacje_plikowe.h"

int main() {
    GameState game;
    
    // Wczytujemy plik
    if (!wczytajMape(&game, "assets/level1.txt")) {
        return 1; // Konczymy gre jesli brak pliku
    }

    // Testowy wydruk mapy w konsoli
    printf("Mapa wczytana poprawnie! Pozycja gracza: X:%d, Y:%d\n\n", game.player_x, game.player_y);
    for (int i = 0; i < game.height; i++) {
        for (int j = 0; j < game.width; j++) {
            printf("%c", game.map[i][j]);
        }
        printf("\n");
    }

    freeGame(&game);
    return 0;
}