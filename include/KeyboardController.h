#pragma once
#include <SDL.h>

#include "Component.h"
#include "Vector2D.h"
#include "Constants.h"
#include "SoundManager.h"

class TransformComponent;
class SpriteComponent;

class KeyboardController : public Component
{
public:
	TransformComponent* transform;
	const uint8_t* keystates = SDL_GetKeyboardState(NULL);
	SDL_Scancode up;
	SDL_Scancode down;
	SDL_Scancode left;
	SDL_Scancode right;
	SDL_Scancode fire;

	SpriteComponent* sprite;

	//for attack cooldown in between shots
	uint32_t lastFireTime = 0;
	
	KeyboardController() = default;
	KeyboardController(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, SDL_Scancode fire, Vector2D fireVelocity);
	~KeyboardController() = default;

	void init() override;
	void update() override;

	uint32_t getFireCooldown() { return this->fireCooldown + this->fireCooldownMod > 0 ? this->fireCooldown + this->fireCooldownMod : 0; };

	void modifyAtkSpeed(int8_t modifier);
	void resetAtkSpeedMod();

private:
	//for creation of projectiles
	TransformComponent* player; //for starting position of projectile
	Vector2D fireVelocity; //decide source of projectile and flying direction
	// SoundManager* soundEffect = Game::assets->getSound;
	//SoundManager* soundEffect = new SoundManager();

	uint32_t fireCooldown = 1000; //in ms can be adjusted to change possible attack-speed
	int32_t fireCooldownMod = 0;
};
