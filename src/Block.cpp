#include "Block.hpp"
#include "TextureManager.hpp"
#include <math.h>
#include <vector>

using namespace std;

const vector<char*> BLOCK_FILES = {"../assets/dirt.png", "../assets/grass.png"};
// const int SCREEN_HEIGHT = 640;
// const int SCREEN_WIDTH = 800;
const int BLOCK_WIDTH = 32;
const int BLOCK_HEIGHT = 32;

Block::Block() {}
Block::~Block() {}

void Block::init(int _x, int _y) {
    // loads file as texture
    blockTex = TextureManager::LoadTexture(BLOCK_FILES[rand() % 2]); //TODO add more colors?

    // adjust height and width of our image box.
    dest.w = BLOCK_WIDTH;
    dest.h = BLOCK_HEIGHT;

    dest.x = _x;
    dest.y = _y;

    isDestroyed = false;
}

void Block::render() {
    if (!isDestroyed) {
        //SDL_RenderCopy(renderer, blockTex, NULL, &dest);
        TextureManager::Draw(blockTex, &dest);
    }
}
