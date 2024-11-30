#include "TextureManager.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <VEGO.h>
#include <linux/soundcard.h>

#include "GameInternal.h"


void TextureManager::addSingleTexture(Textures texture, const char* filePath) {
	auto sdlTexture = IMG_LoadTexture(VEGO_Game().renderer, filePath);

	if (sdlTexture == nullptr)
		throw std::runtime_error(std::string("Couldn't load texture '") + filePath + "'");

	this->texture_cache.emplace(texture, sdlTexture);
	std::cout << "Loaded texture at " << filePath << std::endl;
}

void TextureManager::addTextures(const std::map<Textures, const char*> &textures) {
	for (auto texture : textures) {
		addSingleTexture(texture.first, texture.second);
	}
}


SDL_Texture* TextureManager::loadTexture(Textures texture) {
	auto it = this->texture_cache.find(texture);

	if (it != this->texture_cache.end())
		return it->second;

	std::cout << "ERROR: Couldn't load texture!" << std::endl;
	return nullptr;
}

void TextureManager::draw(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, bool flipped)
{
	SDL_RendererFlip flip = flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyEx(renderer, texture, &src, &dest, 0, NULL, flip);
}

SDL_Texture* TextureManager::loadMapTileTexture(const char *path) {

	//returns tile if it exists already
	if(mapTile_texture_cache.contains(std::string(path)))
		return mapTile_texture_cache.find(std::string(path))->second;

	auto newTexture = IMG_LoadTexture(VEGO_Game().renderer, path);

	if (newTexture == nullptr)
		throw std::runtime_error(std::string("Couldn't load texture '") + path + "'");

	this->mapTile_texture_cache.emplace(std::string(path), newTexture);

	return newTexture;
}
