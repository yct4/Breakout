#include <stdio.h>
#include <SDL2/SDL.h>
#include "Game.hpp"

Game* game;

void waitInStartScreen();
void waitInRoundScreen();

int main(int argc, char *argv[]) {

    const int FPS = 40;
    const int FRAME_DELAY = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Plant the Lawn!!!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT, false);

    waitInStartScreen();

    while (!game->exiting()) {

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart; // how long handleever, update, and render takes
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }

        if(!game->running()) {
            waitInStartScreen();
        }
    }


    game->clean();

    return EXIT_SUCCESS;
}

void waitInStartScreen() {
    while (!game->running()) {
        game->renderStartScreen();
    }
}
