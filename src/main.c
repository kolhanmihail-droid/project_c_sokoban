#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/logika_gry.h"
#include "../include/operacje_plikowe.h"
#include "../include/gui.h"

// SDL wymaga specyficznego zapisu funkcji main
int main(int argc, char* argv[]) {
    GameState game;
    
    if (!wczytajMape(&game, "assets/level1.txt")) {
        return 1;
    }

    if (!initGUI(game.width, game.height)) {
        printf("Brak bibliotek GUI!\n");
        return 1;
    }

    int gramy = 1;
    SDL_Event event;

    // Glowna petla gry
    while (gramy) {
        renderGame(&game);

        // Oczekiwanie i lapanie wcisnietych klawiszy przez SDL
        while (SDL_PollEvent(&event)) {
            // Zamkniecie okna krzyzykiem (X)
            if (event.type == SDL_QUIT) {
                gramy = 0;
            } 
            // Klawiatura
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    case SDLK_UP:    movePlayer(&game, 0, -1); break;
                    case SDLK_s:
                    case SDLK_DOWN:  movePlayer(&game, 0, 1); break;
                    case SDLK_a:
                    case SDLK_LEFT:  movePlayer(&game, -1, 0); break;
                    case SDLK_d:
                    case SDLK_RIGHT: movePlayer(&game, 1, 0); break;
                    case SDLK_z:     undoMove(&game); break;
                    case SDLK_q:
                    case SDLK_ESCAPE: gramy = 0; break;
                }
            }
        }
    }

    closeGUI();
    freeGame(&game);
    return 0;
}