#include "AnimationHandler.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "TextureManager.h"

SpriteComponent::SpriteComponent(const char* path)
{
	setTexture(path);
}

SpriteComponent::SpriteComponent(const char* path, bool isAnimated)
{
	animated = isAnimated;

	Animation* idle = new Animation((int)AnimationType::IDLE, 2, 200);
	Animation* walk = new Animation((int)AnimationType::WALK, 2, 200);

	animations.emplace(IDLE, idle);
	animations.emplace(WALK, walk);

	play(IDLE);

	setTexture(path);
}

SpriteComponent::~SpriteComponent()
{
	// SDL_DestroyTexture(this->texture);
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
	TextureManager::get().draw(this->texture, this->srcRect, this->destRect);
}

void SpriteComponent::play(AnimationType type) 
{
	animationIndex = animations.at(type)->index;
	frames = animations.at(type)->frames;
	speed = animations.at(type)->speed;
}