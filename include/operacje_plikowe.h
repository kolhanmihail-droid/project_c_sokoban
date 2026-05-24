#ifndef OPERACJE_PLIKOWE_H
#define OPERACJE_PLIKOWE_H
#include "logika_gry.h" // Potrzebujemy dostepu do GameState

// Funkcja zwraca 1 jesli sukces, 0 jesli blad
int wczytajMape(GameState *state, const char *filename);

#endif