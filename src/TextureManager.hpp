#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class TextureManager {
    private:
	    static TTF_Font* font;
	    static SDL_Color textColor;

    public:
	static bool init(const char* fileName);
        static SDL_Texture* LoadTexture(const char* fileName);
        static SDL_Texture* LoadTextureMessage(const char* fileName);
// static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
        static void Draw(SDL_Texture* tex, SDL_Rect* dest);
};

#endif // TextureManager_hpp
