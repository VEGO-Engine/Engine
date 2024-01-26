#pragma once
#include <SDL.h>

#include "Component.h"
#include "Vector2D.h"

class TransformComponent;
class SpriteComponent;

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

	SpriteComponent* sprite;

	//for attack cooldown in between shots
	Uint32 lastFireTime;
	Uint32 fireCooldown = 1000; //in ms can be adjusted to change possible attack-speed

	KeyboardController() = default;
	KeyboardController(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode fire, Vector2D fireVelocity);
	~KeyboardController() = default;

	void init() override;
	void update() override;

private:
	//for creation of projectiles
	TransformComponent* player; //for starting position of projectile
	Vector2D fireVelocity; //decide source of projectile and flying direction
};