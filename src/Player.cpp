#include "Player.hpp"

#include "TextureManager.hpp"

const char* Player::PLAYER_FILE = "../assets/pong_player.png";
const int SCREEN_HEIGHT = 640;
const int SCREEN_WIDTH = 800;

Player::Player(int _left, int _right, int _x, int _y) : scancode_left(_left), scancode_right(_right), init_x(_x), init_y(_y) {};
Player::~Player() {}

void Player::init() {
        // loads file as texture
    playerTex = TextureManager::LoadTexture(PLAYER_FILE);

    // connects our texture with dest to control position
    SDL_QueryTexture(playerTex, NULL, NULL, &dest.w, &dest.h);

    // adjust height and width of our image box.
    dest.w /= 2;
    dest.h /= 2;

    // sets initial-position of player
    dest.x = init_x;
    dest.y = init_y;

    // speed of player
    speed = 300;

    // player score
    score = 0;
}

void Player::render() {
    TextureManager::Draw(playerTex, &dest); // player
}

SDL_Rect* Player::getRect() {
    return &dest;
}

void Player::move(SDL_Event& event) {
    // keyboard API for key pressed
    if (event.key.keysym.scancode == scancode_left) {
        dest.x -= speed / 10;
    } else if (event.key.keysym.scancode == scancode_right) {
        dest.x += speed / 10;
    }

    // right boundary 
    if (dest.x + dest.w > SCREEN_WIDTH) {
        dest.x = SCREEN_WIDTH - dest.w; 
    }

    // left boundary 
    if (dest.x < 0) {
        dest.x = 0; 
    }

    // bottom boundary 
    if (dest.y + dest.h > SCREEN_HEIGHT) {
        dest.y = SCREEN_HEIGHT - dest.h; 
    }

}

void Player::reset() {
    // sets initial x-position of object
    dest.x = init_x;

    // sets initial y-position of object
    dest.y = init_y;
    score = 0;
}

bool Player::hasWon() {
    return score == 5;
}

int Player::getScore() {
    return score;
}

void Player::incScore() {
    score++;
}
