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

    static const int BLOCK_WIDTH = 32;
    static const int BLOCK_HEIGHT = 32;

    void init(int _x, int _y, int _color);
    void render();

    void changeColor(int _color);

    void reset() {
        isDestroyed = false;
    };

    void destroy() {
        isDestroyed = true;
    };

    bool getIsDestroyed() {
        return isDestroyed;
    }

    int getColor() {
        return color;
    }

    SDL_Rect* getRect() {
        return &dest;
    }

    enum BlockType {
        WATER = 0,
        GRASS = 1,
        DIRT = 2
    };

private:
    SDL_Rect dest;
    SDL_Texture* blockTex;

    bool isDestroyed;
    int color;

};

#endif // Block_hpp