#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"
#include "AnimationHandler.h"
#include "Defines.h"
#include <map>

class SpriteComponent : public Component
{
	public:
		int animationIndex = 0;

		std::map<AnimationType, Animation*> animations;

	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;

		bool animated = false;
		int frames = 0;
		int speed = 100;

	public:
		SpriteComponent() = default;
		SpriteComponent(const char* path)
		{
			setTexture(path);
		}

		SpriteComponent(const char* path, bool isAnimated)
		{
			animated = isAnimated;

			Animation* idle = new Animation((int)AnimationType::IDLE, 2, 200);
			Animation* walk = new Animation((int)AnimationType::WALK, 2, 200);

			animations.emplace(IDLE, idle);
			animations.emplace(WALK, walk);

			play(IDLE);

			setTexture(path);
		}

		~SpriteComponent()
		{
			SDL_DestroyTexture(this->texture);
		}

		void setTexture(const char* path)
		{
			this->texture = TextureManager::get().loadTexture(path);
		}

		void init() override
		{
			this->transform = &entity->getComponent<TransformComponent>();

			this->srcRect.x = this->srcRect.y = 0;
			this->srcRect.w = transform->width;
			this->srcRect.h = transform->height;
		}

		void update() override
		{
			if (animated)
			{
				srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
			}

			srcRect.y = animationIndex * transform->height;



			this->destRect.x = this->transform->position.x;
			this->destRect.y = this->transform->position.y;
			this->destRect.w = transform->width * transform->scale;
			this->destRect.h = transform->height * transform->scale;
		}

		void draw() override
		{
			TextureManager::get().draw(this->texture, this->srcRect, this->destRect);
		}

		void play(AnimationType type)
		{
			animationIndex = animations.at(type)->index;
			frames = animations.at(type)->frames;
			speed = animations.at(type)->speed;
		}
};
