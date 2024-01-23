#include "TextureManager.h"
#include <cstdio>
#include "Game.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	auto it = this->texture_cache.find(fileName);
	if (it != this->texture_cache.end()) {
		return it->second;
	}
	auto texture = IMG_LoadTexture(Game::renderer, fileName);
	this->texture_cache.emplace(fileName, texture);
	return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}