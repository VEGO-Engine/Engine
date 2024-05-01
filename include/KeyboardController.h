#pragma once
#include <SDL.h>

#include "Component.h"
#include "Vector2D.h"
#include "Constants.h" // TODO: change so gamespecific constants are in own file
#include "SoundManager.h"
#include "Input.h"

class TransformComponent;
class SpriteComponent;

class KeyboardController : public Component
{
public:
	KeyboardController(Input* input, Key up, Key down, Key left, Key right, Key fire, Vector2D fireVelocity);
	~KeyboardController() = default;
	
	void init() override;
	void update() override;
	void modifyAtkSpeed(int8_t modifier);

private:
	Input* m_input;
	Key m_up;
	Key m_down;
	Key m_left;
	Key m_right;
	Key m_fire;

	TransformComponent* m_transform;
	SpriteComponent* m_sprite;

	TransformComponent* m_player; //for starting position of projectile
	Vector2D m_fireVelocity; //decide source of projectile and flying direction

	//for attack cooldown in between shots
	uint32_t m_lastFireTime = 0;
	uint32_t m_fireCooldown = 1000; //in ms can be adjusted to change possible attack-speed
};
