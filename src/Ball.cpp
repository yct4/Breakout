#include "Ball.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"
#include <math.h>

const char* Ball::BALL_FILE = "../assets/ball.png";
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 800;

const int INIT_X_VELOCITY = 1;
const int INIT_Y_VELOCITY = 4;
const int VELOCITY_INCREMENT = 2;

Ball::Ball() {}
Ball::~Ball() {}

void Ball::init() {
    // loads file as texture
    ballTex = TextureManager::LoadTexture(BALL_FILE);

    // connects our texture with dest to control position
    SDL_QueryTexture(ballTex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 20;
    dest.h /= 20;

    // sets initial x-position of object middle of screen
    dest.x = (SCREEN_WIDTH - dest.w) / 2;

    // sets initial y-position of object middle of screen
    dest.y = (SCREEN_HEIGHT - dest.h) / 2;

    // speed of ball
    velocity_x = INIT_X_VELOCITY;
    velocity_y = INIT_Y_VELOCITY;

}

// returns 1 while between rounds else returns 0
void Ball::move(Player* player1) {

    //hits player paddle
    if (SDL_HasIntersection(player1->getRect(), &dest)) {
        velocity_y *= -1;
        velocity_x = rand() % ANGLE_RANGE - (ANGLE_RANGE-1) / 2;
    }

    // TODO increment velocity after clearing a level (ie clearing all blocks from a map)
    //right boundary, dest.x is for upper left corner
    if (dest.x + dest.w >= SCREEN_WIDTH) {
        dest.x = SCREEN_WIDTH - dest.w; 
        velocity_x *= -1;
    }

    // left boundary, dest.y is for upper left corner of the ball
    if (dest.x <= 0) {
        dest.x = 0; 
        velocity_x *= -1;
    }

    dest.x += velocity_x;
    dest.y += velocity_y;
}

void Ball::render() {
    TextureManager::Draw(ballTex, &dest);
}

void Ball::reset() {
    // sets initial x-position of object middle of screen
    dest.x = (SCREEN_WIDTH - dest.w) / 2;

    // sets initial y-position of object middle of screen
    dest.y = (SCREEN_HEIGHT - dest.h) / 2;

    // speed of ball
    velocity_x = INIT_X_VELOCITY;
    velocity_y = INIT_Y_VELOCITY;
}

void Ball::resetPosition() {
        // sets initial x-position of object middle of screen
    dest.x = (SCREEN_WIDTH - dest.w) / 2;

    // sets initial y-position of object middle of screen
    dest.y = (SCREEN_HEIGHT - dest.h) / 2;
}