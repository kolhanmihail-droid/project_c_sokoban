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

// Zmienia pozycje gracza o podany wektor (dx, dy)
void movePlayer(GameState *state, int dx, int dy) {
    int new_x = state->player_x + dx;
    int new_y = state->player_y + dy;

    char target_cell = state->map[new_y][new_x];

    // 1. Jesli uderzamy w sciane - koniec, nie ruszamy sie
    if (target_cell == '#') return;

    // 2. Jesli to skrzynia ($), sprawdzamy czy mozemy ja popchnac
    if (target_cell == '$') {
        int box_new_x = new_x + dx;
        int box_new_y = new_y + dy;
        char box_target = state->map[box_new_y][box_new_x];

        // Skrzynie mozna popchnac tylko na puste pole (' ') lub cel ('.')
        if (box_target == ' ' || box_target == '.') {
            state->map[box_new_y][box_new_x] = '$'; // Nowa pozycja skrzyni
            state->map[new_y][new_x] = ' ';         // Stara pozycja skrzyni staje sie pusta
        } else {
            return; // Za skrzynia jest sciana lub inna skrzynia, wiec gracz tez stoi
        }
    }

    // 3. Ruch gracza (czyszczenie starej pozycji, ustawienie nowej)
    state->map[state->player_y][state->player_x] = ' '; 
    state->map[new_y][new_x] = '@';

    // Aktualizacja wspolrzednych w strukturze
    state->player_x = new_x;
    state->player_y = new_y;
}