#pragma once

#include "ECS.h"
#include <SDL_render.h>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "TextureEnumBase.h"

class TextureManager
{
	public:
		TextureManager(Manager* manager) : manager(manager) {}
		~TextureManager() {
			for (auto& it : this->texture_cache) {
				SDL_DestroyTexture(it.second);
			}
		}

		void addSingleTexture(TexturesEnum texture, const char* filePath);
		void addTextures(const std::map<TexturesEnum, const char*>& textures);
		SDL_Texture* loadTexture(TexturesEnum texture);
        static std::vector<SDL_Rect> splitSpriteSheet(SDL_Texture* spriteSheet, int width, int height, int spritesOnSheet);
		static void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, bool flipped = false);
	private:
		Manager* manager;
		std::map<TexturesEnum, SDL_Texture*> texture_cache;
};