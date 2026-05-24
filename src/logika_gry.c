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
    state->history = NULL; // Na starcie lista historii jest pusta
    printf("Sukces: Zaalokowano pamiec na mape %dx%d.\n", w, h);
}

// Funkcja sprzatajaca pamiec po zakonczeniu gry
void freeGame(GameState *state) {
    while (state->history != NULL) {
        MoveNode *temp = state->history;
        state->history = state->history->next;
        free(temp);
    }
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
    int pushed_box = 0;

    if (target_cell == '#') return;

    if (target_cell == '$') {
        int box_new_x = new_x + dx;
        int box_new_y = new_y + dy;
        char box_target = state->map[box_new_y][box_new_x];

        if (box_target == ' ' || box_target == '.') {
            state->map[box_new_y][box_new_x] = '$'; 
            pushed_box = 1;
        } else {
            return; 
        }
    }

    // LISTA JEDNOKIERUNKOWA: Tworzymy nowy wezel historii
    MoveNode *node = (MoveNode *)malloc(sizeof(MoveNode));
    node->dx = dx;
    node->dy = dy;
    node->pushed_box = pushed_box;
    node->next = state->history;
    state->history = node; // Doklejamy na poczatek listy

    state->map[state->player_y][state->player_x] = ' '; 
    state->map[new_y][new_x] = '@';
    state->player_x = new_x;
    state->player_y = new_y;
}

// Funkcja cofajaca ruch uzywajaca listy jednokierunkowej
void undoMove(GameState *state) {
    if (state->history == NULL) return; // Brak ruchow do cofniecia

    MoveNode *node = state->history; // Pobieramy ostatni ruch

    // 1. Cofamy gracza
    state->map[state->player_y][state->player_x] = ' ';
    state->player_x -= node->dx;
    state->player_y -= node->dy;
    state->map[state->player_y][state->player_x] = '@';

    // 2. Jesli pchalismy skrzynie, tez ja cofamy
    if (node->pushed_box) {
        // Skrzynia uciekla na odleglosc 2*dx od starej pozycji, musimy ja wziac i cofnac
        int box_current_x = state->player_x + 2 * node->dx;
        int box_current_y = state->player_y + 2 * node->dy;
        
        state->map[box_current_y][box_current_x] = ' '; // Usuwamy skrzynie z nowej pozycji
        state->map[state->player_y + node->dy][state->player_x + node->dx] = '$'; // Kladziemy przed graczem
    }

    // 3. Usuwamy wezel z pamieci (dealokacja)
    state->history = node->next;
    free(node);
}