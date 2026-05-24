#include <stdio.h>
#include <stdlib.h>
#include "../include/logika_gry.h"
#include "../include/operacje_plikowe.h"

int main() {
    GameState game;
    if (!wczytajMape(&game, "assets/level1.txt")) {
        return 1;
    }

    int gramy = 1;
    char wejscie;

    while (gramy) {
        // Czyszczenie ekranu (komenda "cls" w Windows, w Linuksie to "clear")
        system("cls"); 
        
        printf("Sokoban - Wersja Konsolowa\n");
        printf("Ruch: W, A, S, D, Z-cofanie | Wyjscie: Q\n\n");

        // Rysowanie planszy
        for (int i = 0; i < game.height; i++) {
            for (int j = 0; j < game.width; j++) {
                printf("%c", game.map[i][j]);
            }
            printf("\n");
        }

        // Pobranie ruchu od gracza (spacja przed %c zjada niechciane Entery)
        printf("\nTwoj ruch: ");
        scanf(" %c", &wejscie);

        // Rozpoznawanie klawiszy
        if (wejscie == 'w' || wejscie == 'W') movePlayer(&game, 0, -1);
        if (wejscie == 's' || wejscie == 'S') movePlayer(&game, 0, 1);
        if (wejscie == 'a' || wejscie == 'A') movePlayer(&game, -1, 0);
        if (wejscie == 'd' || wejscie == 'D') movePlayer(&game, 1, 0);
        if (wejscie == 'z' || wejscie == 'Z') undoMove(&game); // Cofanie ruchu
        if (wejscie == 'q' || wejscie == 'Q') gramy = 0; // Wyjscie z pętli
    }

    freeGame(&game);
    printf("Dzieki za gre!\n");
    return 0;
}