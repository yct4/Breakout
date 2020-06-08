#include "Game.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

const char* START_BUTTON_FILE = "../assets/start_button.png";
const char* CONTINUE_BUTTON_FILE = "../assets/continue.jpg";
const vector<char*> NUMBER_FILES = {"../assets/zero.jpg","../assets/one.png", "../assets/two.jpg", "../assets/three.jpg", "../assets/four.png", "../assets/five.jpg"};
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 800;

const int PLAYER_SCALE = 2;
const int PLAYER_IMG_HEIGHT = 27;
const int PLAYER_IMG_WIDTH = 208;

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

    // initialize score number pictures
    for(int i = 0; i < 6; i++) {
        numberTex[i] = TextureManager::LoadTexture(NUMBER_FILES[i]);

        SDL_QueryTexture(numberTex[i], NULL, NULL, &player1ScoreRect.w, &player1ScoreRect.h);
        player1ScoreRect.w /= 4;
        player1ScoreRect.h /= 4;

    }

    // sets initial position of player2 score to middle of right half of screen
    player1ScoreRect.x = (SCREEN_WIDTH - player1ScoreRect.w) * 3 / 4;
    player1ScoreRect.y = (SCREEN_HEIGHT - player1ScoreRect.h) / 4;

    // game over banner
    gameOverTex = TextureManager::LoadTexture("../assets/gameOver.png");
    SDL_QueryTexture(gameOverTex, NULL, NULL, &gameOverRect.w, &gameOverRect.h);
    gameOverRect.x = (SCREEN_WIDTH - gameOverRect.w) / 2;
    gameOverRect.y = (SCREEN_HEIGHT - gameOverRect.h) * 3 / 4;

    // init map
    map = new Map();

    // init game objects
    ball = new Ball();
    ball->init();

    // init player, start in the middle of the bottom of the screen
    player1 = new Player(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT);
    int x1_init = (SCREEN_WIDTH - PLAYER_IMG_WIDTH / PLAYER_SCALE) / 2; 
    int y1_init = (SCREEN_HEIGHT - PLAYER_IMG_HEIGHT / PLAYER_SCALE);
    player1->init(x1_init, y1_init, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN);

}

// TODO: for other games, unsused in pong
void Game::DrawMap() {
    int type = 0;

    for(int row = 0; row < 20; row++) {
        for(int col = 0;  col < 25; col++) {
            type = map->map[row][col];

            map->dest.x = col * 32;
            map->dest.y = row * 32;

            switch (type) {
                case 0:
                    TextureManager::Draw(map->water, map->src, map->dest);
                    break;
                case 1: 
                    TextureManager::Draw(map->grass, map->src, map->dest);
                    break;
                case 2:
                    TextureManager::Draw(map->dirt, map->src, map->dest);
                    break;
                default:
                    break;
            }
        }
    }
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
    ball->move(player1);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 255,255,255,255); // set color to write
    SDL_RenderClear(renderer); // clear renderer with latest set color

    map->DrawMap();
    //render game objects
    player1->render(renderer); // player
    ball->render(renderer);

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
    SDL_RenderCopy(renderer, buttonTex, NULL, &startButtonRect);

    // render screen
    SDL_RenderPresent(renderer);
    reset();
};

void Game::reset() { // reset player and ball to initial positions and reset ball velocity
    player1->reset();
    ball->reset();
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game Cleaned\n");
}