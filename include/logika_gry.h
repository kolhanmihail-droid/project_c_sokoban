#ifndef LOGIKA_GRY_H
#define LOGIKA_GRY_H

// Struktura przechowujaca caly stan gry Sokoban
typedef struct {
    char **map;      // Podwojny wskaznik - dynamiczna tablica 2D na mape
    int width;       // Szerokosc poziomu
    int height;      // Wysokosc poziomu
    int player_x;    // Pozycja gracza na osi X
    int player_y;    // Pozycja gracza na osi Y
} GameState;

// Deklaracje funkcji
void initGame(GameState *state, int w, int h);
void freeGame(GameState *state);

#endif