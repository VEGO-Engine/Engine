#pragma once
#include "SDL.h"

class GameObject
{
	public:
		GameObject(const char* texturesheet, int x, int y);
		~GameObject() = default;

		void update();
		void render();

	private:
		int xPos;
		int yPos;

		SDL_Texture* objTexture;
		SDL_Rect srcRect;
		SDL_Rect destRect;
};

