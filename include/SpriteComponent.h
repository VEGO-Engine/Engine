#pragma once
#include "Components.h"
#include "SDL.h"
#include "TextureManager.h"

class SpriteComponent : public Component
{
	public:
		SpriteComponent() = default;
		SpriteComponent(const char* path)
		{
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
;
			
		}

		void update() override
		{
			this->destRect.x = this->transform->position.x;
			this->destRect.y = this->transform->position.y;
			this->destRect.w = transform->width * transform->scale;
			this->destRect.h = transform->height * transform->scale;
		}

		void draw() override
		{
			TextureManager::get().draw(this->texture, this->srcRect, this->destRect);
		}

	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect srcRect, destRect;

};
