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
        static const int MAP_HEIGHT = 15; // Height of map in number of blocks
        static const int BLOCK_ROWS = 8; // how many rows are grass initially

        void LoadMap(int** arr);
        void init(Ball* _ball, Player* _player1);
        bool update(Ball* _ball, Player* _player1);
        void DrawMap();
        void reset();

    //private:

	Ball* ball;
	Player* player1;

        SDL_Rect src, dest;
        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* water;

        int** map;
	int score;
};



#endif // Map_hpp
