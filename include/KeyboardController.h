#pragma once
#include "SDL.h"
#include "Component.h"

class TransformComponent;

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

	KeyboardController() = default;
	KeyboardController(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right/*, SDL_Scancode action*/);
	~KeyboardController() = default;

	void init() override;
	void update() override;
};
