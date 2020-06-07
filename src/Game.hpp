#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Map.hpp"
#include "Ball.hpp"
#include "Player.hpp"

class Game {

    public:
        int close = 0;

        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void DrawMap();
        void renderBlock(SDL_Window* window, SDL_Rect* box);
        void handleEvents();
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


    private:
        SDL_Window* window;
        bool isRunning;
        bool isExited;
        Map* map;
        Ball* ball;
        Player* player1;

        // start button
        SDL_Rect startButtonRect;
        SDL_Texture* buttonTex;

        //banners
        SDL_Rect gameOverRect;
        SDL_Texture* gameOverTex;

        // score
        SDL_Rect player1ScoreRect;
        SDL_Texture* numberTex[]; // must be last line of class
};

#endif // Game_hpp
