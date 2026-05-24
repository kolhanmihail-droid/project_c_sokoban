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

// Funkcja zapisujaca obecny stan mapy do pliku
void zapiszGre(GameState *state, const char *filename) {
    FILE *file = fopen(filename, "w"); // "w" oznacza write (zapisz/nadpisz)
    if (file == NULL) {
        printf("BLAD: Nie mozna zapisac gry do pliku %s!\n", filename);
        return;
    }

    for (int i = 0; i < state->height; i++) {
        for (int j = 0; j < state->width; j++) {
            fprintf(file, "%c", state->map[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("SUKCES: Gra zostala zapisana w %s\n", filename);
    logAction("Gracz zapisal stan gry."); // Automatyczny log
}

// Funkcja dopisujaca logi z gry (np. bledy lub dzialania)
void logAction(const char *message) {
    // "a" oznacza append (dopisz na koncu pliku)
    FILE *file = fopen("logs/historia.log", "a"); 
    if (file != NULL) {
        fprintf(file, "[LOG]: %s\n", message);
        fclose(file);
    }
}
