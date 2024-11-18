#pragma once

#include "ECS.h"
#include "SDL3/SDL_surface.h"
#include <SDL3/SDL_render.h>
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

		std::map<std::string, SDL_Texture*> texture_cache;

		SDL_Texture* loadTexture(const char* fileName);
        static std::vector<SDL_Rect> splitSpriteSheet(SDL_Texture* spriteSheet, int width, int height, int spritesOnSheet);
		static void draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_FRect src, SDL_FRect dest, bool flipped = false);

		void setScaleMode(SDL_ScaleMode scaleMode) { this->scaleMode = scaleMode; }
	private:
		SDL_ScaleMode scaleMode = SDL_SCALEMODE_NEAREST;
		Manager* manager;
};