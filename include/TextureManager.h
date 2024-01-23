#pragma once

#include "Game.h"
#include "SDL_render.h"
#include <map>

struct cmp_str
{
   bool operator()(char const *a, char const *b) const {
      return strcmp(a, b) < 0;
   }
};

class TextureManager
{
    public:
        static TextureManager& get()
        {
            static TextureManager instance;
            return instance;
        }
        
    private:
        TextureManager() {}
        ~TextureManager() {
        	for (auto& it : this->texture_cache) {
        		SDL_DestroyTexture(it.second);
        	}
        }

    public:
        TextureManager(TextureManager const&) = delete;
        void operator=(TextureManager const&) = delete;

        std::map<const char*, SDL_Texture*, cmp_str> texture_cache;

		SDL_Texture* loadTexture(const char* fileName);
        static std::vector<SDL_Rect> splitSpriteSheet(SDL_Texture* spriteSheet, int width, int height, int spritesOnSheet);
		static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};