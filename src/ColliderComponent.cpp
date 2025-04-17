#include "ColliderComponent.h"

#include "CollisionHandler.h"
#include "Entity.h"
#include "GameInternal.h"
#include "TransformComponent.h"
#include <iostream>

ColliderComponent::ColliderComponent(const char* tag)
{
	this->tag = tag;
	this->collision = true;
	this->hitboxScale = 1;
}

ColliderComponent::ColliderComponent(const char* tag, float hitboxScale) //adding hitboxScale helps scaling hitbox and texture/entity seperately
{
	this->tag = tag;
	this->hitboxScale = hitboxScale;
	this->collision = true;
}

void ColliderComponent::init()
{
	if (!entity->hasComponent<TransformComponent>()) {
		entity->addComponent<TransformComponent>();
	}

	transform = &entity->getComponent<TransformComponent>();
	this->update(0);
}

void ColliderComponent::update(uint_fast16_t diffTime)
{
	collider.x = transform->position.x - (transform->width - transform->width * transform->scale * this->hitboxScale) / 2;
	collider.y = transform->position.y - (transform->width - transform->width * transform->scale * this->hitboxScale) / 2;


	collider.w = (transform->width * transform->scale) * this->hitboxScale;
	collider.h = (transform->height * transform->scale) * this->hitboxScale;
}

void ColliderComponent::removeCollision()
{
	this->collision = false;
}