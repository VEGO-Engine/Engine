#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	this->objTexture = TextureManager::get().loadTexture(texturesheet);
	this->xPos = x;
	this->yPos = y;
}

GameObject::~GameObject()
{

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
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
