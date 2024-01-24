#include "ColliderComponent.h"

#include "Entity.h"
#include "Game.h"
#include "TransformComponent.h"

ColliderComponent::ColliderComponent(const char* tag)
{
	this->tag = tag;
    this->hasCollision = true;
}

void ColliderComponent::init()
{
	if (!entity->hasComponent<TransformComponent>()) {
		entity->addComponent<TransformComponent>();
	}

	transform = &entity->getComponent<TransformComponent>();
	Game::colliders.push_back(this);
}

void ColliderComponent::update()
{
	collider.x = transform->position.x;
	collider.y = transform->position.y;

	collider.w = transform->width * transform->scale;
	collider.h = transform->height * transform->scale;
}

void ColliderComponent::removeCollision()
{
    this->hasCollision = false;
}