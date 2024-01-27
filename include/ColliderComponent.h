#pragma once

#include <SDL.h>

#include "Component.h"

class TransformComponent;

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	const char* tag;
	TransformComponent* transform;
	bool hasCollision; //added for removing collision of destroyed projectiles
	float hitboxScale; //adds a seperate variable for the scale of the hitbox (not the sprite) so each sprite can have a different hitbox size if needed

	ColliderComponent(const char* tag);
	ColliderComponent(const char* tag, float hitboxScale);

	void init() override;
	void update() override;
    void removeCollision();
};