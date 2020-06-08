#ifndef Map_hpp
#define Map_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class Map {

    public:

        Map();
        ~Map();

        void LoadMap(int arr[20][25]);
        void DrawMap();

    //private:

        SDL_Rect src, dest;
        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* water;

        static const int MAP_WIDTH = 20;
        static const int MAP_HEIGHT = 25;

        int map[MAP_WIDTH][MAP_HEIGHT];
};



#endif // Map_hpp