#include "Game.hpp"
#include "TextureManager.hpp"
#include "Player.hpp"
#include <stdio.h>
#include <vector>
#include <cassert>

using namespace std;

const char* START_BUTTON_FILE = "../assets/start_button.png";
const char* FONT_FILE = "../assets/open-sans/OpenSans-Regular.ttf";

// player image constants
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

    // initialize game to start in Start Screen
    isRunning = false;

    // initialize start button
    buttonTex = TextureManager::LoadTexture(START_BUTTON_FILE);
    // connects our texture with startButtonRect to control position
    SDL_QueryTexture(buttonTex, NULL, NULL, &startButtonRect.w, &startButtonRect.h);
    // sets initial position of object middle of screen
    startButtonRect.x = (SCREEN_WIDTH - startButtonRect.w) / 2;
    startButtonRect.y = (SCREEN_HEIGHT - startButtonRect.h) / 2;

    // init game objects
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

    // init score    
    try {
	   fontTextureManager = new TextureManager(FONT_FILE); 
    }
    catch (int e) {
	   if (e == -1) {
	       printf("TTF init failed!!!\n");
	   } else if (e == 2) {
	       printf("font init failed!!\n");
	   }
	    
    }
    
    prev_score = 0;
    scoreTex = fontTextureManager->LoadTextureMessage("test text");
    // connects our texture with scoreRect to control position
    SDL_QueryTexture(scoreTex, NULL, NULL, &scoreRect.w, &scoreRect.h);
    // sets initial position of object middle of screen
    scoreRect.x = (SCREEN_WIDTH - scoreRect.w) / 2;
    scoreRect.y = (SCORE_HEIGHT - scoreRect.h) / 2;

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

int isKeydownEvent(void* userdata, SDL_Event* event) {
    return event->type == SDL_KEYDOWN || event->type == SDL_QUIT;
}


void Game::update() {
    isRunning = map->update(ball, player1);
    if (map->score != prev_score) {
        assert(sprintf(str, "Score: %d", map->score) > 0);
        assert(scoreTex != NULL);
        scoreTex = fontTextureManager->LoadTextureMessage(str);
        prev_score = map->score;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0,0,0,0); // set color to write
    SDL_RenderClear(renderer); // clear renderer with latest set color

    map->DrawMap();
    //render game objects
    player1->render(); // player
    ball->render();
    // render score to screen
    TextureManager::Draw(scoreTex, &scoreRect);

    SDL_RenderPresent(renderer);
}

void Game::renderStartScreen() {
    SDL_SetEventFilter(NULL, NULL);
	
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
		    // set Event filter
                    void* userdata = NULL;
                    SDL_SetEventFilter(isKeydownEvent, userdata);

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
