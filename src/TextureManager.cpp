#include "TextureManager.h"

#include <memory>
#include <stdexcept>
#include <string>

#include "GameInternal.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	auto it = this->texture_cache.find(fileName);
	if (it != this->texture_cache.end()) {
		return it->second;
	}
	auto texture = IMG_LoadTexture(this->manager->getGame()->renderer, fileName);
	if (texture == NULL) throw std::runtime_error(std::string("Couldn't load texture '") + fileName + "'");
	this->texture_cache.emplace(std::string(fileName), texture);
	printf("Loaded texture at '%s'\n", fileName);
	return texture;
}

void TextureManager::draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, bool flipped)
{
	SDL_RendererFlip flip = flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, NULL, flip);
}