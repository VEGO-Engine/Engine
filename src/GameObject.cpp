#include "GameObject.h"

#include "SDL_error.h"
#include "TextureManager.h"
#include "GameInternal.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	// seems not to be used, and was using deprecated functionality
	SDL_SetError("GameObject not implemented");

	this->xPos = x;
	this->yPos = y;
}

void GameObject::update()
{
	xPos++;
	yPos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.h = srcRect.h *2;
	destRect.w = srcRect.w *2;
	destRect.x = xPos;
	destRect.y = yPos;
}

void GameObject::render()
{
	SDL_SetError("GameObject not implemented");
	// SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
