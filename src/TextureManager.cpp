#include "TextureManager.hpp"
#include "Game.hpp"

bool TextureManager::init(const char* fileName) {
    if (TTF_Init() == -1) {
        return false;
    }
    font = TTF_OpenFont(fileName, 28);
    if (font == NULL) {
        return false;
    }
    textColor = {255, 255, 255};
    return true;
}

SDL_Texture* TextureManager::LoadTextureMessage(const char* fileName) {
    SDL_Surface* tempSurface = IMG_Load(fileName);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
    SDL_Surface* tempSurface = TTF_RenderText_Solid(font, fileName, textColor);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

// void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
//     SDL_RenderCopy(Game::renderer, tex, &src, &dest);
// }

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect* dest) {
    SDL_RenderCopy(Game::renderer, tex, NULL, dest);
}
