#include "TransformComponent.h"

#include "CollisionHandler.h"
#include "ColliderComponent.h"
#include "Constants.h"
#include "Entity.h"
#include "GameInternal.h"
#include "Vector2D.h"
#include <cstdio>
#include <initializer_list>
#include <iostream>
#include <optional>

#include "SoundManager.h"

TransformComponent::TransformComponent(int scale)
{
	position.zero();
	this->scale = scale;
}

TransformComponent::TransformComponent(float x, float y, int scale)
{
	this->position.x = x;
	this->position.y = y;
	this->scale = scale;
}

TransformComponent::TransformComponent(float x, float y, int w, int h, int scale)
{
	this->position.x = x;
	this->position.y = y;
	this->width = w;
	this->height = h;
	this->scale = scale;
}

void TransformComponent::init()
{
	direction.zero();
}

void TransformComponent::update(uint_fast16_t diffTime)
{
	direction.x = direction.x > 0 ? 1 : direction.x < 0 ? -1 : 0;
	direction.y = direction.y > 0 ? 1 : direction.y < 0 ? -1 : 0;
	
	float multiplier = direction.x != 0 && direction.y != 0 ? 0.707 : 1; // normalizes vector; only works if directions are in increments of 45°
	Vector2D positionChange(
		direction.x * this->getSpeed() * multiplier * diffTime * (1.f/1000),
		direction.y * this->getSpeed() * multiplier * diffTime * (1.f/1000)
	);

	if (this->entity->hasComponent<ColliderComponent>() 
	&& this->entity->getComponent<ColliderComponent>().hasCollision()){
		this->setPositionAfterCollision(positionChange);
	}

	position += positionChange;
}

int TransformComponent::getSpeed()
{ 
	return (this->entity->hasComponent<DataComponent>()
			? this->entity->getComponent<DataComponent>().getEntry<int>("speed").value_or(0)
			: 0);
}

void TransformComponent::setPositionAfterCollision(Vector2D& positionChange)
{
	std::initializer_list<Entity::GroupLabel> colliders = { Entity::GroupLabel::MAPTILES, Entity::GroupLabel::COLLIDERS };
	// [getAnyIntersection example code]
	IntersectionBitSet intersections =
		(CollisionHandler::getIntersectionWithBounds(entity, Vector2D(positionChange.x, 0)) |
			(this->entity->getManager()
			.getGame()->collisionHandler->getAnyIntersection<IntersectionBitSet>(entity, Vector2D(positionChange.x, 0), colliders)) &
			IntersectionBitSet("0011")) |
		(CollisionHandler::getIntersectionWithBounds(entity, Vector2D(0, positionChange.y)) |
			(this->entity->getManager()
			.getGame()->collisionHandler->getAnyIntersection<IntersectionBitSet>(entity, Vector2D(0, positionChange.y), colliders)) &
			IntersectionBitSet("1100"));

	if (intersections.test((size_t)Direction::LEFT) || intersections.test((size_t)Direction::RIGHT))
		positionChange.x = 0;

	if (intersections.test((size_t)Direction::UP) || intersections.test((size_t)Direction::DOWN))
		positionChange.y = 0;
	// [getAnyIntersection example code]
}