#ifndef Ball_hpp
#define Ball_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "TextureManager.hpp"
#include "Player.hpp"

class Ball {
public: 
    Ball();
    ~Ball();



    void init();
    bool move(Player* player1);
    void render();
    void reset();
    void resetPosition();
    SDL_Rect* getDestRect() {
        return &dest;
    };

    void getVelocity(int* x, int* y) {
        *x = velocity_x;
        *y = velocity_y;
    }

    void updateVelocity(int x, int y) {
        velocity_x = x;
        velocity_y = y;
    };

    static const char* BALL_FILE;
    static const int ANGLE_RANGE = 5;

private:
    SDL_Rect dest;
    SDL_Rect srcRect, destRect;
    SDL_Texture* ballTex;

    int velocity_x;
    int velocity_y;

};

#endif // Ball_hpp