#ifndef Map_hpp
#define Map_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Block.hpp"
#include "Ball.hpp"

class Map {

    public:

        Map();
        ~Map();

        static const int MAP_WIDTH = 25;
        static const int MAP_HEIGHT = 20;
        static const int BLOCK_ROWS = 8;

        void LoadMap(int** arr);
        void init();
        void update(Ball* ball);
        void DrawMap();
        void reset();

    //private:

        SDL_Rect src, dest;
        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* water;

        int** map;
};



#endif // Map_hpp