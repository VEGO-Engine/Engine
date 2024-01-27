#include "TextureManager.h"

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
	draw(texture, src, dest, false);
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, bool flipped)
{
	SDL_RendererFlip flip = flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(Game::renderer, texture, &src, &dest, 0, NULL, flip);
}