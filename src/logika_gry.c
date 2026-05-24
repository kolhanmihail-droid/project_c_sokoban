#include <stdlib.h>
#include <stdio.h>
#include "../include/logika_gry.h"

// Funkcja tworzaca czysta mape w pamieci
void initGame(GameState *state, int w, int h) {
    state->width = w;
    state->height = h;
    state->player_x = 0;
    state->player_y = 0;

    // Alokacja wierszy (tablica wskaznikow)
    state->map = (char **)malloc(h * sizeof(char *));
    if (state->map == NULL) {
        printf("Blad: Brak pamieci na mape!\n");
        exit(1); // w przypadku bledu krytycznego
    }

    // Alokacja kolumn dla kazdego wiersza
    for (int i = 0; i < h; i++) {
        state->map[i] = (char *)malloc(w * sizeof(char));
        if (state->map[i] == NULL) {
            printf("Blad: Brak pamieci na wiersz %d!\n", i);
            exit(1);
        }
        // Wypelnienie mapy pustymi spacjami
        for (int j = 0; j < w; j++) {
            state->map[i][j] = ' ';
        }
    }
    state->history = NULL; // Na starcie historia jest pusta
    printf("Sukces: Zaalokowano pamiec na mape %dx%d.\n", w, h);
}

// Funkcja sprzatajaca pamiec po zakonczeniu gry
void freeGame(GameState *state) {
    while (state->history != NULL) {
        MoveNode *temp = state->history;
        state->history = state->history->next;
        free(temp);
    }
    // Zwalnianie idzie w odwrotnej kolejnosci 
    for (int i = 0; i < state->height; i++) {
        free(state->map[i]); 
    }
    free(state->map);
    printf("Sukces: Pamiec mapy zwolniona bezpiecznie.\n");
}

void movePlayer(GameState *state, int dx, int dy) {
    int new_x = state->player_x + dx;
    int new_y = state->player_y + dy;
    char target_cell = state->map[new_y][new_x];
    int pushed_box = 0;

    if (target_cell == '#') return;

    // Obsluga pchania skrzyni (zwyklej '$' lub stojacej na celu '*')
    if (target_cell == '$' || target_cell == '*') {
        int box_new_x = new_x + dx;
        int box_new_y = new_y + dy;
        char box_target = state->map[box_new_y][box_new_x];

        if (box_target == ' ' || box_target == '.') {
            // Skrzynia laduje na pustym polu lub na celu (staje sie zlota '*')
            state->map[box_new_y][box_new_x] = (box_target == '.') ? '*' : '$';
            pushed_box = 1;
            // Odkrywamy to, co bylo pod popchnieta skrzynia
            target_cell = (target_cell == '*') ? '.' : ' '; 
        } else {
            return; 
        }
    }

    // Zapis do historii dla Undo
    MoveNode *node = (MoveNode *)malloc(sizeof(MoveNode));
    node->dx = dx;
    node->dy = dy;
    node->pushed_box = pushed_box;
    node->next = state->history;
    state->history = node;

    // Gracz opuszcza aktualne pole (jesli stal na celu '+', zostawia cel '.')
    char current_cell = state->map[state->player_y][state->player_x];
    state->map[state->player_y][state->player_x] = (current_cell == '+') ? '.' : ' ';

    // Gracz wchodzi na nowe pole (jesli to cel '.', staje sie '+')
    state->map[new_y][new_x] = (target_cell == '.') ? '+' : '@';
    state->player_x = new_x;
    state->player_y = new_y;
}

void undoMove(GameState *state) {
    if (state->history == NULL) return;

    MoveNode *node = state->history;

    // Gracz schodzi z obecnego pola do tylu
    char current_cell = state->map[state->player_y][state->player_x];
    state->map[state->player_y][state->player_x] = (current_cell == '+') ? '.' : ' ';

    // Gracz wraca na poprzednie pole
    int prev_x = state->player_x - node->dx;
    int prev_y = state->player_y - node->dy;
    char prev_target = state->map[prev_y][prev_x];
    state->map[prev_y][prev_x] = (prev_target == '.') ? '+' : '@';

    state->player_x = prev_x;
    state->player_y = prev_y;

    // Cofanie skrzyni (jesli byla popchnieta)
    if (node->pushed_box) {
        int box_current_x = state->player_x + 2 * node->dx;
        int box_current_y = state->player_y + 2 * node->dy;
        char box_cell = state->map[box_current_y][box_current_x];
        
        // Zdejmujemy skrzynie z nowej pozycji
        state->map[box_current_y][box_current_x] = (box_cell == '*') ? '.' : ' ';
        
        // Kladziemy ja z powrotem przed graczem
        char box_return_cell = state->map[state->player_y + node->dy][state->player_x + node->dx];
        state->map[state->player_y + node->dy][state->player_x + node->dx] = (box_return_cell == '.') ? '*' : '$';
    }

    state->history = node->next;
    free(node);
}