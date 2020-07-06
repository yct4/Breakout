#ifndef Player_hpp
#define Player_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hpp"

class Player {
public:  
    Player(int _up, int _down, int _x, int _y);
    ~Player();

    int speed = 300;

    void init();
    void render();
    void move(SDL_Event& event);
    void reset();
    bool hasWon();
    int getScore();
    void incScore();
    SDL_Rect* getRect();

    static const char* PLAYER_FILE;

private:
    SDL_Rect dest;
    SDL_Texture* playerTexture;
    SDL_Rect srcRect, destRect;
    SDL_Texture* playerTex;
    const int scancode_left;
    const int scancode_right;

    const int init_x;
    const int init_y;

    int score;

};

#endif // Player_hpp
