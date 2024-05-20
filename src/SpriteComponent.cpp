#include "SpriteComponent.h"

#include <SDL_timer.h>
#include <cstring>
#include <memory>

#include "AnimationHandler.h"
#include "Direction.h"
#include "TextureManager.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Game.h"
#include "Manager.h"

SpriteComponent::SpriteComponent(const char* path)
{
	this->texturePath = path;
}

SpriteComponent::SpriteComponent(
	const char* path,
	bool isAnimated,
	std::map<std::string, std::unique_ptr<Animation>>* animationMap,
	std::string defaultAnimation)
{
	animated = isAnimated;

	animations = animationMap;

	playAnimation(defaultAnimation);

	this->texturePath = path;
}

SpriteComponent::~SpriteComponent()
{
	// SDL_DestroyTexture(this->texture);
}

void SpriteComponent::setTexture(const char* path)
{
	this->texture = this->entity->getManager().getGame()->textureManager->loadTexture(path);
}

void SpriteComponent::init()
{
	setTexture(this->texturePath);

	this->transform = &entity->getComponent<TransformComponent>();

	this->srcRect.x = this->srcRect.y = 0;
	this->srcRect.w = transform->width;
	this->srcRect.h = transform->height;

	this->update();
}

void SpriteComponent::update()
{
	if (animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
	}

	srcRect.y = animationIndex * transform->height;

	this->destRect.x = this->transform->position.x;
	this->destRect.y = this->transform->position.y;
	this->destRect.w = transform->width * transform->scale;
	this->destRect.h = transform->height * transform->scale;
}

void SpriteComponent::draw()
{
	this->entity->getManager().getGame()->textureManager->draw(this->entity->getManager().getGame()->renderer, this->texture, this->srcRect, this->destRect, this->animated && this->flipped);
}

void SpriteComponent::playAnimation(std::string type)
{
	this->animationIndex = animations->at(type)->index;
	this->frames = animations->at(type)->frames;
	this->speed = animations->at(type)->speed;
}

void SpriteComponent::setDirection(Direction direction)
{
	this->flipped = direction == Direction::RIGHT;
}