#include <stdlib.h>
#include <stdio.h>
#include "../include/logika_gry.h"

// Funkcja tworzaca czysta mape w pamieci
void initGame(GameState *state, int w, int h) {
    state->width = w;
    state->height = h;
    state->player_x = 0;
    state->player_y = 0;

    // 1. Alokacja wierszy (tablica wskaznikow)
    state->map = (char **)malloc(h * sizeof(char *));
    if (state->map == NULL) {
        printf("Blad: Brak pamieci na mape!\n");
        exit(1); // Brutalne wyjscie w przypadku bledu krytycznego
    }

    // 2. Alokacja kolumn dla kazdego wiersza
    for (int i = 0; i < h; i++) {
        state->map[i] = (char *)malloc(w * sizeof(char));
        if (state->map[i] == NULL) {
            printf("Blad: Brak pamieci na wiersz %d!\n", i);
            exit(1);
        }
        // Wypelnienie mapy pustymi polami (spacja)
        for (int j = 0; j < w; j++) {
            state->map[i][j] = ' ';
        }
    }
    printf("Sukces: Zaalokowano pamiec na mape %dx%d.\n", w, h);
}

// Funkcja sprzatajaca pamiec po zakonczeniu gry
void freeGame(GameState *state) {
    // Zwalnianie idzie w odwrotnej kolejnosci - najpierw wiersze, potem glowna tablica
    for (int i = 0; i < state->height; i++) {
        free(state->map[i]); 
    }
    free(state->map);
    printf("Sukces: Pamiec mapy zwolniona bezpiecznie.\n");
}