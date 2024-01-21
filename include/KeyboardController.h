#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	SDL_Scancode up;
	SDL_Scancode down;
	SDL_Scancode left;
	SDL_Scancode right;
	SDL_Scancode fire;

    Uint32 lastFireTime;
    Uint32 fireCooldown = 1000;

	KeyboardController();
	KeyboardController(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode fire, Vector2D fireVelocity);

	~KeyboardController();

	void init() override;

	void update() override;

private:
    TransformComponent* player;
    Vector2D fireVelocity;
};
