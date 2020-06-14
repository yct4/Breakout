#include "Map.hpp"
#include "TextureManager.hpp"
#include <stdlib.h>
#include <string.h>

// const int BLOCK_ROWS = 8;
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
    for(int i = 0; i < MAP_HEIGHT; i++) {
        free(lvl1[i]);
    }
    free(lvl1);

    for(int i = 0; i < MAP_HEIGHT; i++) {
        free(map[i]);
    }
    free(map);
}

void Map::LoadMap(int** arr) {
    //memcpy(map, arr, sizeof(map[0][0])*MAP_WIDTH*MAP_HEIGHT); // causes the game to crash 
    for(int i = 0; i < MAP_HEIGHT; i++){
        for(int j = 0; j < MAP_WIDTH; j++) {
            map[i][j] = arr[i][j];
        }
    }
}

void Map::init() {
    lvl1 = (int**)malloc(sizeof(int*) * MAP_HEIGHT); 
    for (int j = 0; j < MAP_HEIGHT; j++) {
        lvl1[j] = (int*)malloc(MAP_WIDTH * sizeof(int));
    }

    map = (int**)malloc(sizeof(int*) * MAP_HEIGHT); 
    for (int j = 0; j < MAP_HEIGHT; j++) {
        map[j] = (int*)malloc(MAP_WIDTH * sizeof(int));
    }

    // make lvl1 map
    for(int i = 0; i < MAP_HEIGHT; i++) {
        memset(lvl1[i], 0, sizeof(lvl1[0][0]) * MAP_WIDTH);
    }
    for(int r = 0; r < BLOCK_ROWS; r++) { // top BLOCK_ROWS are blocks
        for(int c = 0; c < MAP_WIDTH; c++) {
            lvl1[r][c] = rand() % 2 + 1; // 1 or 2 TODO: add more colors of blocks
            // Block* b = new Block();
            // b->init(r*32, c*32);
            // blockList.push_back(b);
        }
    }

    LoadMap(lvl1);


}

void Map::update(Ball* ball) {

}

void Map::DrawMap() {
    int type = 0;

    for(int row = 0; row < MAP_HEIGHT; row++) {
        for(int col = 0;  col < MAP_WIDTH; col++) {
            type = map[row][col];

            dest.x = col * 32;
            dest.y = row * 32;

            switch (type) {
                case 0:
                    TextureManager::Draw(water, &dest);
                    break;
                case 1: 
                    TextureManager::Draw(grass, &dest);
                    break;
                case 2:
                    TextureManager::Draw(dirt, &dest);
                    break;
                default:
                    break;
            }
        }
    }

}

