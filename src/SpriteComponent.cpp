#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "TextureManager.h"
#include "Entity.h"

SpriteComponent::SpriteComponent(const char* path)
{
	setTexture(path);
}

SpriteComponent::~SpriteComponent()
{
	SDL_DestroyTexture(this->texture);
}

void SpriteComponent::setTexture(const char* path)
{
	this->texture = TextureManager::get().loadTexture(path);
}

void SpriteComponent::init()
{
	this->transform = &entity->getComponent<TransformComponent>();

	this->srcRect.x = this->srcRect.y = 0;
	this->srcRect.w = transform->width;
	this->srcRect.h = transform->height;
}

void SpriteComponent::update()
{
	this->destRect.x = this->transform->position.x;
	this->destRect.y = this->transform->position.y;
	this->destRect.w = transform->width * transform->scale;
	this->destRect.h = transform->height * transform->scale;
}

void SpriteComponent::draw()
{
	TextureManager::get().draw(this->texture, this->srcRect, this->destRect);
}


