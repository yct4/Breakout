#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Map.hpp"
#include "Ball.hpp"
#include "Player.hpp"
#include "Block.hpp"

int isKeydownEvent(void* userdata, SDL_Event* event);
class Game {

    public:

        Game();
        ~Game();
	
        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void DrawMap();
        void renderBlock(SDL_Window* window, SDL_Rect* box);
        void handleEvents();
	//static int  isKeydownEvent(const SDL_Event* event, void* userdata);
        void update();
        void render();
        void clean();
        void reset();

        void renderStartScreen();

        static SDL_Renderer* renderer;

        bool running() {
            return isRunning;
        };

        bool exiting() {
            return isExited;
        };

        static const int SCORE_HEIGHT = 64; // takes up 2 rows of blocks (each block is 32x32)
        static const int SCREEN_HEIGHT = Map::MAP_HEIGHT * Block::BLOCK_HEIGHT + SCORE_HEIGHT;
        static const int SCREEN_WIDTH = Map::MAP_WIDTH * Block::BLOCK_WIDTH;

	Player* player1;

    private:
        SDL_Window* window;
        bool isRunning;
        bool isExited;
        Map* map;
        Ball* ball;

        // start button
        SDL_Rect startButtonRect;
        SDL_Texture* buttonTex;

	// score
	SDL_Rect scoreRect;
        SDL_Texture* scoreTex;
	TextureManager* fontTextureManager;
	int prev_score;
	char str[20];


};

#endif // Game_hpp
