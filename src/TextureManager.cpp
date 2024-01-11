#include "TextureManager.h"

SDL_Texture* TextureManager::loadTexture(const char* fileName)
{
	return IMG_LoadTexture(Game::renderer, fileName);
}

void TextureManager::draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}