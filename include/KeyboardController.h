#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "Defines.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	SDL_Scancode up;
	SDL_Scancode down;
	SDL_Scancode left;
	SDL_Scancode right;
	//SDL_Scancode action;

	SpriteComponent* sprite;

	KeyboardController();
	KeyboardController(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right/*, SDL_Scancode action*/);

	~KeyboardController();

	void init() override;

	void update() override;
};
