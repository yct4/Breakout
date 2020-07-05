#include "Block.hpp"
#include "TextureManager.hpp"
#include <math.h>
#include <vector>

using namespace std;

const vector<char*> BLOCK_FILES = {"..assets/water.png", "../assets/grass.png", "../assets/dirt.png"};

// const int SCREEN_HEIGHT = 640;
// const int SCREEN_WIDTH = 800;
const int BLOCK_WIDTH = 32;
const int BLOCK_HEIGHT = 32;

Block::Block() {}
Block::~Block() {}

void Block::init(int _x, int _y, int _color) {
    // loads file as texture
    this->blockTex = TextureManager::LoadTexture(BLOCK_FILES[_color]); //TODO add more colors?
    this->color = _color;

    // adjust height and width of our image box.
    dest.w = BLOCK_WIDTH;
    dest.h = BLOCK_HEIGHT;

    dest.x = _x;
    dest.y = _y;

    isDestroyed = false;
}

void Block::changeColor(int _color) {
    this->blockTex = TextureManager::LoadTexture(BLOCK_FILES[_color]);
    this->color = _color; 
};

void Block::render() {
    if (!isDestroyed) {
        TextureManager::Draw(this->blockTex, &dest);
    } else {
        SDL_Texture* grassTex = TextureManager::LoadTexture(BLOCK_FILES[GRASS]);
        TextureManager::Draw(grassTex, &dest);
    }
}
