#ifndef GUI_H
#define GUI_H
#include "logika_gry.h"

// Funkcje do zarzadzania oknem gry
int initGUI(int width, int height);
void renderGame(GameState *state);
void closeGUI();

#endif