#ifndef LOGIKA_GRY_H
#define LOGIKA_GRY_H

// Wymog na 5.0 - Dynamiczna struktura danych (Lista jednokierunkowa)
typedef struct MoveNode {
    int dx;
    int dy;
    int pushed_box;        // 1 jesli popchnelismy skrzynie, 0 jesli nie
    struct MoveNode *next; // Wskaznik na poprzedni ruch
} MoveNode;

typedef struct {
    char **map;      
    int width;       
    int height;      
    int player_x;    
    int player_y;    
    MoveNode *history; // Poczatek naszej listy z historia ruchow
} GameState;

void initGame(GameState *state, int w, int h);
void freeGame(GameState *state);
void movePlayer(GameState *state, int dx, int dy);

// NOWE: Funkcja do cofania ruchu
void undoMove(GameState *state);

#endif