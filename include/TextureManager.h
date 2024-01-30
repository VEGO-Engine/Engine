#pragma once

#include <SDL_render.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

class TextureManager
{
	public:
		TextureManager() {}
		~TextureManager() {
			for (auto& it : this->texture_cache) {
				SDL_DestroyTexture(it.second);
			}
		}

		std::map<std::string, SDL_Texture*> texture_cache;

		SDL_Texture* loadTexture(const char* fileName);
        static std::vector<SDL_Rect> splitSpriteSheet(SDL_Texture* spriteSheet, int width, int height, int spritesOnSheet);
		static void draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, bool flipped = false);
};