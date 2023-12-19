#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;
	const char* tag;
	TransformComponent* transform;

	ColliderComponent(const char* tag)
	{
		this->tag = tag;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
		Game::colliders.push_back(this);
	}

	void update() override
	{
		collider.x = transform->position.x;
		collider.y = transform->position.y;

		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};