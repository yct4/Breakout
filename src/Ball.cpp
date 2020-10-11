#include "Ball.hpp"
#include "Player.hpp"
#include "TextureManager.hpp"
#include <math.h>
#include "Game.hpp"

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

void Ball::render() {
    TextureManager::Draw(ballTex, &dest);
}

void Ball::reset() {
    // sets initial x-position of object middle of screen
    dest.x = (SCREEN_WIDTH - dest.w) / 2;

    // sets initial y-position of object middle of screen
    dest.y = (SCREEN_HEIGHT - Game::SCORE_HEIGHT - dest.h) / 2;

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
