#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/gui.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const int TILE_SIZE = 64; // Jeden kwadrat na mapie bedzie mial 64x64 piksele

int initGUI(int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Blad: Nie udalo sie zainicjowac SDL! %s\n", SDL_GetError());
        return 0;
    }
    
    // Tworzymy okno dopasowane do rozmiaru mapy
    window = SDL_CreateWindow("Sokoban - Projekt C", 
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                              width * TILE_SIZE, height * TILE_SIZE, SDL_WINDOW_SHOWN);
    if (!window) return 0;
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return 0;
    
    return 1; // Sukces
}

void renderGame(GameState *state) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < state->height; i++) {
        for (int j = 0; j < state->width; j++) {
            SDL_Rect rect = { j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE };
            char cell = state->map[i][j];

            if (cell == '#') {
                SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255); // Szary mur
                SDL_RenderFillRect(renderer, &rect);
            } else if (cell == '$') {
                SDL_SetRenderDrawColor(renderer, 139, 69, 19, 255);   // Brazowa skrzynia
                SDL_RenderFillRect(renderer, &rect);
            } else if (cell == '*') { // NOWE: Skrzynia na celu
                SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);   // Zlota skrzynia!
                SDL_RenderFillRect(renderer, &rect);
            } else if (cell == '.') {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);     // Zielony cel
                SDL_RenderFillRect(renderer, &rect);
            } else if (cell == '@' || cell == '+') { // NOWE: Gracz obojetnie gdzie stoi
                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);     // Niebieski gracz
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void closeGUI() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void resizeWindow(int width, int height) {
    if (window != NULL) {
        SDL_SetWindowSize(window, width * TILE_SIZE, height * TILE_SIZE);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }
}