#pragma once
#include "SDL.h"
#include "Component.h"

class TransformComponent;

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	const char* tag;
	TransformComponent* transform;
	bool hasCollision; //added for removing collision of destroyed projectiles

	ColliderComponent(const char* tag);

	void init() override;
	void update() override;
    void removeCollision();
};