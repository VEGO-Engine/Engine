#include "SpriteComponent.h"

#include <SDL_timer.h>
#include <cstring>
#include <memory>

#include "AnimationHandler.h"
#include "Direction.h"
#include "ProjectileComponent.h"
#include "RenderObject.h"
#include "TextureManager.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "GameInternal.h"
#include "Manager.h"
#include "VEGO.h"

SpriteComponent::SpriteComponent(const char* path, int zIndex) : RenderObject(zIndex, VEGO_Game().renderManager), textureXOffset(0), textureYOffset(0)
{
	this->texturePath = path;
}

SpriteComponent::SpriteComponent(const char* path, int xOffset, int yOffset, int zIndex) : RenderObject(zIndex, VEGO_Game().renderManager), textureXOffset(xOffset), textureYOffset(yOffset)
{
	this->texturePath = path;
}

SpriteComponent::SpriteComponent(
	const char* path,
	bool isAnimated,
	std::map<std::string, std::unique_ptr<Animation>>* animationMap,
	std::string defaultAnimation,
	int zIndex) : RenderObject(zIndex, VEGO_Game().renderManager), textureXOffset(0), textureYOffset(0)
{
	animated = isAnimated;

	animations = animationMap;

	playAnimation(defaultAnimation);

	this->texturePath = path;
}

SpriteComponent::~SpriteComponent() {}

void SpriteComponent::setTexture(const char* path)
{
	this->texture = VEGO_Game().textureManager->loadTexture(path);
}

void SpriteComponent::init()
{
	setTexture(this->texturePath);

	this->transform = &entity->getComponent<TransformComponent>();

	this->srcRect.w = transform->width;
	this->srcRect.h = transform->height;
	this->srcRect.x = this->textureXOffset * this->srcRect.w;
	this->srcRect.y = this->textureYOffset * this->srcRect.h;;

	this->update();
}

void SpriteComponent::update()
{
	// This code is not compatible for animated tiles
	if (animated) {
		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);

		srcRect.y = animationIndex * transform->height;
	}

	this->destRect.x = this->transform->position.x;
	this->destRect.y = this->transform->position.y;
	this->destRect.w = transform->width * transform->scale;
	this->destRect.h = transform->height * transform->scale;
}

void SpriteComponent::draw()
{
	this->entity->getManager().getGame()->textureManager->draw(VEGO_Game().renderer, this->texture, this->srcRect, this->destRect, this->animated && this->flipped);
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