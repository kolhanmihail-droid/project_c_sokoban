#include <SDL2/SDL.h>
#include <stdio.h>
#include "../include/logika_gry.h"
#include "../include/operacje_plikowe.h"
#include "../include/gui.h"

int main(int argc, char* argv[]) {
    // SYSTEM POZIOMOW
    const char* poziomy[] = {
        "assets/level1.txt", 
        "assets/level2.txt", 
        "assets/level3.txt"
    };
    int aktualny_poziom = 0;
    int max_poziomy = 3;

    GameState game;
    
    // Wczytanie pierwszego poziomu
    if (!wczytajMape(&game, poziomy[aktualny_poziom])) {
        return 1;
    }

    if (!initGUI(game.width, game.height)) {
        printf("Brak bibliotek GUI!\n");
        return 1;
    }

    int gramy = 1;
    SDL_Event event;

    while (gramy) {
        renderGame(&game);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gramy = 0;
            } 
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                    case SDLK_UP:    movePlayer(&game, 0, -1); logAction("Ruch w gore"); break;
                    case SDLK_s:
                    case SDLK_DOWN:  movePlayer(&game, 0, 1); logAction("Ruch w dol"); break;
                    case SDLK_a:
                    case SDLK_LEFT:  movePlayer(&game, -1, 0); logAction("Ruch w lewo"); break;
                    case SDLK_d:
                    case SDLK_RIGHT: movePlayer(&game, 1, 0); logAction("Ruch w prawo"); break;
                    case SDLK_z:     undoMove(&game); logAction("Cofniecie ruchu (Undo)"); break;
                    case SDLK_F5:    zapiszGre(&game, "saves/zapis.txt"); break;
                    
                    // NOWE: Restart poziomu
                    case SDLK_r:     
                        freeGame(&game);
                        wczytajMape(&game, poziomy[aktualny_poziom]);
                        resizeWindow(game.width, game.height); // ROZCIAGNIECIE OKNA
                        logAction("Zresetowano poziom.");
                        break;
                    
                    // NOWE: Nastepny poziom
                    case SDLK_n:     
                        aktualny_poziom++;
                        if (aktualny_poziom >= max_poziomy) {
                            printf("Gratulacje! Przeszedles wszystkie poziomy!\n");
                            gramy = 0; // Koniec gry
                        } else {
                            freeGame(&game);
                            wczytajMape(&game, poziomy[aktualny_poziom]);
                            resizeWindow(game.width, game.height); // ROZCIAGNIECIE OKNA
                            logAction("Przejscie do nastepnego poziomu.");
                        }
                        break;
                    case SDLK_q:
                    case SDLK_ESCAPE: gramy = 0; logAction("Zamkniecie gry."); break;
                }
            }
        }
    }

    closeGUI();
    freeGame(&game);
    return 0;
}