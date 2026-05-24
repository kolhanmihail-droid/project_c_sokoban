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

    // 1. SKANOWANIE PLIKU: Szukamy szerokosci i wysokosci
    int w = 0;
    int h = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        h++; // Kazda linijka to nowy wiersz
        int len = 0;
        // Liczymy znaki do momentu napotkania konca linii (Entera)
        while (buffer[len] != '\0' && buffer[len] != '\n' && buffer[len] != '\r') {
            len++;
        }
        if (len > w) {
            w = len; // Zapisujemy najdluzszy wiersz jako szerokosc mapy
        }
    }

    // 2. ALOKACJA PAMIECI
    initGame(state, w, h);

    // 3. WCZYTYWANIE MAPY: Cofamy plik na poczatek i czytamy na gotowo
    rewind(file); 
    int row = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL && row < state->height) {
        for (int col = 0; col < state->width; col++) {
            char c = buffer[col];
            
            // Zabezpieczenie przed krotkimi liniami w pliku tekstowym
            if (c == '\n' || c == '\r' || c == '\0') {
                for (int k = col; k < state->width; k++) {
                    state->map[row][k] = ' '; // Wypelnij reszte pusta przestrzenia
                }
                break;
            }

            state->map[row][col] = c;
            
            // Szukamy gracza
            if (c == '@' || c == '+') {
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
    FILE *file = fopen(filename, "w");
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
    logAction("Gracz zapisal stan gry.");
}

// Funkcja dopisujaca logi z gry
void logAction(const char *message) {
    FILE *file = fopen("logs/historia.log", "a"); 
    if (file != NULL) {
        fprintf(file, "[LOG]: %s\n", message);
        fclose(file);
    }
}