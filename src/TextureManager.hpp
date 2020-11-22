#ifndef TextureManager_hpp
#define TextureManager_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class TextureManager {
    private:
	     TTF_Font* font;
	     SDL_Color textColor;

    public:
	//TextureManager(const char* fileName);
	TextureManager(const char* fileName) {
     
            if (TTF_Init() == -1) {
	        throw -1;
	    }
            font = TTF_OpenFont(fileName, 28);
            if (font == NULL) {
	        throw 2;
	    }
            textColor = {255, 255, 255};
        };

	~TextureManager();
	//bool init(const char* fileName);
         static SDL_Texture* LoadTexture(const char* fileName);
         SDL_Texture* LoadTextureMessage(const char* fileName);
//  void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
         static void Draw(SDL_Texture* tex, SDL_Rect* dest);
};

#endif // TextureManager_hpp
