#include "Game.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

const char* START_BUTTON_FILE = "../assets/start_button.png";

// player image constants
const int PLAYER_SCALE = 2;
const int PLAYER_IMG_HEIGHT = 27;
const int PLAYER_IMG_WIDTH = 208;

// ball image constants
//const int BALL_SCALE = 20;
//const int BALL_IMG_WIDTH = ;
//const int BALL_IMG_HEIGHT = ;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {}
Game::~Game() {}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    // init screen
    int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : 0;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL could not initialize! SDL ERROR: %d", SDL_GetError());
        isRunning = false;
        return;
    }
    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (window) {
        printf("window created!\n");
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        printf("renderer created!\n");
    }

    // init other variables
    isRunning = false;

    // initialize start button
    buttonTex = TextureManager::LoadTexture(START_BUTTON_FILE);
    // connects our texture with startButtonRect to control position
    SDL_QueryTexture(buttonTex, NULL, NULL, &startButtonRect.w, &startButtonRect.h);
        // sets initial position of object middle of screen
    startButtonRect.x = (SCREEN_WIDTH - startButtonRect.w) / 2;
    startButtonRect.y = (SCREEN_HEIGHT - startButtonRect.h) / 2;

    // init game objects
    //int ball_x_init = (SCREEN_WIDTH - BALL_IMG_WIDTH / BALL_SCALE) / 2;
    //int ball_y_init = (SCREEN_HEIGHT - BALL_IMG_HEIGHT / BALL_SCALE) / 2;
    //ball = new Ball(ball_x_init, ball_y_init);
    ball = new Ball();
    ball->init();

    // init player, start in the middle of the bottom of the screen
    int x1_init = (SCREEN_WIDTH - PLAYER_IMG_WIDTH / PLAYER_SCALE) / 2; 
    int y1_init = (SCREEN_HEIGHT - PLAYER_IMG_HEIGHT / PLAYER_SCALE);
    player1 = new Player(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, x1_init, y1_init);
    player1->init();


    // init map
    map = new Map();
    map->init(ball, player1);

}


void Game::handleEvents() {
    SDL_Event event; 

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN){ 
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { // exit game
                isExited = true;
                break;
            }
            player1->move(event); // player

        } else if (event.type == SDL_QUIT) { // exit game if window is closed
            isExited = true;
            break;
        }
    }
}


void Game::update() {
    // isRunning = ball->move(player1);
    isRunning = map->update(ball, player1);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0,0,0,0); // set color to write
    SDL_RenderClear(renderer); // clear renderer with latest set color

    map->DrawMap();
    //render game objects
    player1->render(); // player
    ball->render();

    SDL_RenderPresent(renderer);
}

void Game::renderStartScreen() {
    SDL_Event event; 
    int mouse_x = 0;
    int mouse_y = 0;

    SDL_SetRenderDrawColor(renderer, 0,0,0,0); // set color to write
    SDL_RenderClear(renderer); // clear renderer with latest set color

    // Events mangement
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEBUTTONDOWN) { // clicked on start button
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouse_x = event.button.x;
                mouse_y = event.button.y;
                if( ( mouse_x > startButtonRect.x ) && ( mouse_x < startButtonRect.x + startButtonRect.w ) && ( mouse_y > startButtonRect.y ) && ( mouse_y < startButtonRect.y + startButtonRect.h ) ) {
                    isRunning = true;
                }
            }
        } else if (event.type == SDL_KEYDOWN){ 
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                isExited = true;
                isRunning = true;
            }
        } else if (event.type == SDL_QUIT) { // exit game if window is closed
            isExited = true;
            isRunning = true;
            break;
        }
    } 

    // render start button to screen
    TextureManager::Draw(buttonTex, &startButtonRect);

    // render screen
    SDL_RenderPresent(renderer);
    reset();
};

void Game::reset() { // reset player and ball to initial positions and reset ball velocity
    player1->reset();
    ball->reset();
    map->reset();
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game Cleaned\n");
}
