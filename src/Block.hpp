#ifndef Block_hpp
#define Block_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hpp"
#include "Player.hpp"

class Block {
public: 
    Block();
    ~Block();

    void init(int _x, int _y);
    void render();
    void reset() {
        isDestroyed = false;
    };

    void destroy() {
        isDestroyed = true;
    };

private:
    SDL_Rect dest;
    SDL_Texture* blockTex;

    bool isDestroyed;

};

#endif // Block_hpp