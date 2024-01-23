#pragma once
#include "SDL.h"
#include "Game.h"

class TransformComponent;

class SpriteComponent : public Component
{
	public:
		SpriteComponent() = default;
		SpriteComponent(const char* path);
		~SpriteComponent();

		void setTexture(const char* path);

		void init() override;
		void update() override;
		void draw() override;

	private:
		TransformComponent* transform;
		SDL_Texture* texture;
		SDL_Rect srcRect;
		SDL_Rect destRect;
};
