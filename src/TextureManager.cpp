#include "TextureManager.h"

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
	SDL_SetTextureScaleMode(texture, this->scaleMode); // linear scaling results in blurry images
	this->texture_cache.emplace(std::string(fileName), texture);
	printf("Loaded texture at '%s'\n", fileName);
	return texture;
}

void TextureManager::draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_FRect src, SDL_FRect dest, bool flipped)
{
	SDL_FlipMode flip = flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderTextureRotated(renderer, texture, &src, &dest, 0, NULL, flip);
}