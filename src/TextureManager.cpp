#include "TextureManager.h"
#include <cstdio>
#include <stdexcept>
#include <string>
#include "Game.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	auto it = this->texture_cache.find(fileName);
	if (it != this->texture_cache.end()) {
		return it->second;
	}
	auto texture = IMG_LoadTexture(Game::renderer, fileName);
	if (texture == NULL) throw std::runtime_error(std::string("Couldn't load texture '") + fileName + "'");
	this->texture_cache.emplace(fileName, texture);
	printf("Loaded texture at '%s'\n", fileName);
	return texture;
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}