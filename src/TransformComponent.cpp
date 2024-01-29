#include "TransformComponent.h"

#include "CollisionHandler.h"
#include "ColliderComponent.h"
#include "Constants.h"
#include "Entity.h"
#include "Game.h"
#include "Vector2D.h"
#include <cstdio>
#include <initializer_list>
#include <iostream>

TransformComponent::TransformComponent()
{
	position.zero();
}

TransformComponent::TransformComponent(int scale)
{
	position.zero();
	this->scale = scale;
}

TransformComponent::TransformComponent(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
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

void TransformComponent::update()
{
	// if(velocity.x != 0 && velocity.y != 0)

	float multiplier = direction.x != 0 && direction.y != 0 ? 0.707 : 1; // normalizes vector; only works if directions are in increments of 45°
	Vector2D positionChange(
		direction.x * speed * multiplier,
		direction.y * speed * multiplier
	);

	// TODO: move to separate functions

	if (this->entity->hasGroup((size_t) GroupLabel::PLAYERS)) {
		IntersectionBitSet intersections =
			(CollisionHandler::getIntersectionWithBounds(entity, Vector2D(positionChange.x, 0)) |
			(Game::collisionHandler->getAnyIntersection<IntersectionBitSet>(entity, Vector2D(positionChange.x, 0), {GroupLabel::MAPTILES, GroupLabel::COLLIDERS})) &
				IntersectionBitSet("0011")) |
			(CollisionHandler::getIntersectionWithBounds(entity, Vector2D(0, positionChange.y)) |
			(Game::collisionHandler->getAnyIntersection<IntersectionBitSet>(entity, Vector2D(0, positionChange.y), {GroupLabel::MAPTILES, GroupLabel::COLLIDERS})) &
				IntersectionBitSet("1100"));

		if (intersections.test((size_t) direction::LEFT) || intersections.test((size_t) direction::RIGHT))
			positionChange.x = 0;		

		if (intersections.test((size_t) direction::UP) || intersections.test((size_t) direction::DOWN))
			positionChange.y = 0;
	}

	position += positionChange;
};