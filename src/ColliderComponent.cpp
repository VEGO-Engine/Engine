#include "ColliderComponent.h"

#include "Entity.h"
#include "Game.h"
#include "TransformComponent.h"
#include <iostream>

ColliderComponent::ColliderComponent(const char* tag)
{
	this->tag = tag;
	this->hasCollision = true;
	this->hitboxScale = 1;
}

ColliderComponent::ColliderComponent(const char* tag, float hitboxScale) //adding hitboxScale helps scaling hitbox and texture/entity seperately
{
	this->tag = tag;
	this->hitboxScale = hitboxScale;
	this->hasCollision = true;
}

void ColliderComponent::init()
{
	if (!entity->hasComponent<TransformComponent>()) {
		entity->addComponent<TransformComponent>();
	}

	if (strcmp(this->tag, "projectile") == 0) {
		this->isProjectile = true;
	}

	transform = &entity->getComponent<TransformComponent>();
	Game::colliders.push_back(this);
}

void ColliderComponent::update()
{
	collider.x = transform->position.x;
	collider.y = transform->position.y;


	collider.w = (transform->width * transform->scale) * this->hitboxScale;
	collider.h = (transform->height * transform->scale) * this->hitboxScale;
}

void ColliderComponent::removeCollision()
{
	this->hasCollision = false;
}

void ColliderComponent::handleCollision(Vector2D& entityPos, SDL_Rect& entityCollider, SDL_Rect& componentCollider)
{
	// collision to right of character
	if (entityPos.x < componentCollider.x)
	{
		entityPos.x = componentCollider.x - entityCollider.w;
	}
	else // collision to left of character
	{
		entityPos.x = componentCollider.x + componentCollider.w;
	}
}