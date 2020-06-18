#include "Map.hpp"
#include "TextureManager.hpp"
#include <stdlib.h>
#include <string.h>

Block*** blockMap;
int** lvl1;

using namespace std;

Map::Map() {
    dirt = TextureManager::LoadTexture("../assets/dirt.png");
    grass = TextureManager::LoadTexture("../assets/grass.png");
    water = TextureManager::LoadTexture("../assets/water.png");

    src.x = src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;

    dest.x = dest.y = 0;
}

Map::~Map() {
    for(int i = 0; i < MAP_HEIGHT; i++) { // free lvl1
        free(lvl1[i]);
    }
    free(lvl1);

    for(int i = 0; i < MAP_HEIGHT; i++) { // free blockMap
        free(blockMap[i]);
    }
    free(blockMap);

    for(int i = 0; i < MAP_HEIGHT; i++) { // free map
        free(map[i]);
    }
    free(map);
}

void Map::LoadMap(int** arr) {
    //memcpy(map, arr, sizeof(map[0][0])*MAP_WIDTH*MAP_HEIGHT); // causes the game to crash 
    for(int r = 0; r < MAP_HEIGHT; r++) { // top BLOCK_ROWS are blocks
        for(int c = 0; c < MAP_WIDTH; c++) {
            if(arr[r][c] > 0) {
                if(blockMap[r][c] == NULL) { // add block
                    Block* b = new Block();
                    //     (  _x,   _y,     color)
                    b->init(c*32, r*32, arr[r][c]);
                    blockMap[r][c] = b;
                } else { // block already exists, change color
                    blockMap[r][c]->changeColor(arr[r][c]);
                    blockMap[r][c]->reset();
                }
            } else { // no block should be in this square for the next level
                if(blockMap[r][c] != NULL) { // delete existing block
                    delete blockMap[r][c];
                    blockMap[r][c] = NULL;
                }
            }
        }
    }
}

void Map::init() {
    lvl1 = (int**)malloc(sizeof(int*) * MAP_HEIGHT); // allocate memory for lvl1
    for (int j = 0; j < MAP_HEIGHT; j++) {
        lvl1[j] = (int*)malloc(MAP_WIDTH * sizeof(int));
    }

    blockMap = (Block***)malloc(sizeof(int*) * MAP_HEIGHT); // allocate memory for blockMap
    for (int j = 0; j < MAP_HEIGHT; j++) {
        blockMap[j] = (Block**)malloc(MAP_WIDTH * sizeof(Block*));
    }

    // make lvl1 map
    for(int i = 0; i < MAP_HEIGHT; i++) {
        memset(lvl1[i], 0, sizeof(lvl1[0][0]) * MAP_WIDTH);
    }

    for(int r = 0; r < MAP_HEIGHT; r++) {
        for(int c = 0; c < MAP_WIDTH; c++) {
            blockMap[r][c] = NULL;
        }
    }

    for(int r = 0; r < BLOCK_ROWS; r++) { // top BLOCK_ROWS are blocks
        for(int c = 0; c < MAP_WIDTH; c++) {
            lvl1[r][c] = rand() % 2 + 1; // 1 or 2 TODO: add more colors of blocks
        }
    }

    LoadMap(lvl1);


}

void Map::update(Ball* ball) {

}

void Map::DrawMap() {

    for(int row = 0; row < MAP_HEIGHT; row++) {
        for(int col = 0; col < MAP_WIDTH; col++) {
            if (blockMap[row][col] != NULL) {
                blockMap[row][col]->render();
            } else {
                dest.x = col * 32;
                dest.y = row * 32;
                TextureManager::Draw(water, &dest);
            }
        }
    }

}

