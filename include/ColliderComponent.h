#pragma once

#include <SDL.h>

#include "Component.h"
#include "Vector2D.h"

class TransformComponent;

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	const char* tag;
	TransformComponent* transform;
	bool hasCollision; //added for removing collision of destroyed projectiles
	float hitboxScale; //adds a seperate variable for the scale of the hitbox (not the sprite) so each sprite can have a different hitbox size if needed

	bool isProjectile = false;

	ColliderComponent(const char* tag);
	ColliderComponent(const char* tag, float hitboxScale);

	void init() override;
	void update() override;
    void removeCollision();

	void handleCollision(Vector2D& characterPos, SDL_Rect& characterCollider, SDL_Rect& componentCollider);

	std::string componentName() override { return "ColliderComponent"; }
};