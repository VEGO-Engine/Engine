#pragma once

#include "ECS.h"
#include <SDL_render.h>
#include <map>
#include <memory>
#include <string>
#include <vector>

class TextureManager
{
	public:
		TextureManager(Manager* manager) : manager(manager) {}
		~TextureManager() {
			for (auto& it : this->texture_cache) {
				SDL_DestroyTexture(it.second);
			}
		}

		SDL_Texture* loadTexture(const char* fileName);
        static std::vector<SDL_Rect> splitSpriteSheet(SDL_Texture* spriteSheet, int width, int height, int spritesOnSheet);
		static void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, bool flipped = false);
	private:
		Manager* manager;
		std::map<std::string, SDL_Texture*> texture_cache;
};