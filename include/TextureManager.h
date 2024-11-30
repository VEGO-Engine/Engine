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
			for (auto& it : this->mapTile_texture_cache) {
				SDL_DestroyTexture(it.second);
			}
		}

		void addSingleTexture(Textures texture, const char* filePath);
		void addTextures(const std::map<Textures, const char*>& textures);
		SDL_Texture* loadTexture(Textures texture);
        static std::vector<SDL_Rect> splitSpriteSheet(SDL_Texture* spriteSheet, int width, int height, int spritesOnSheet);
		static void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, bool flipped = false);

		SDL_Texture* loadMapTileTexture(const char* path);

	private:
		Manager* manager;
		std::map<Textures, SDL_Texture*> texture_cache;
		std::map<std::string, SDL_Texture*> mapTile_texture_cache;
};