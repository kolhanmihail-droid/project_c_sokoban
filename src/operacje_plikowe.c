#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/operacje_plikowe.h"

int wczytajMape(GameState *state, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("BLAD: Nie mozna otworzyc pliku %s!\n", filename);
        return 0;
    }

    // Dla uproszczenia w trybie turbo zakladamy staly rozmiar na ten moment 5x5
    // Zwalniamy ewentualna stara pamiec i alokujemy nowa
    initGame(state, 5, 5);

    char buffer[256];
    int row = 0;

    // Czytamy plik linijka po linijce
    while (fgets(buffer, sizeof(buffer), file) != NULL && row < state->height) {
        for (int col = 0; col < state->width; col++) {
            state->map[row][col] = buffer[col];
            
            // Jesli znalezlismy gracza, zapisujemy jego pozycje
            if (buffer[col] == '@') {
                state->player_x = col;
                state->player_y = row;
            }
        }
        row++;
    }

    fclose(file);
    return 1;
}