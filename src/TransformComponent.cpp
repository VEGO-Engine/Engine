#include "TransformComponent.h"

#include "CollisionHandler.h"
#include "ColliderComponent.h"
#include "Constants.h"
#include "Entity.h"
#include "Game.h"
#include "Vector2D.h"
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
	velocity.zero();
}

void TransformComponent::update()
{
	// if(velocity.x != 0 && velocity.y != 0)

	float multiplier = velocity.x != 0 && velocity.y != 0 ? 0.707 : 1; //normalizes vector
	Vector2D positionChange(
		velocity.x * speed * multiplier,
		velocity.y * speed * multiplier
	);

	// TODO: move to separate functions

	if (this->entity->hasGroup((size_t) GroupLabel::PLAYERS)) {
		IntersectionBitSet intersectionsX = CollisionHandler::getIntersectionWithBounds(entity, positionChange);
		for (auto& collider : Game::collisionHandler->getColliders(GroupLabel::MAPTILES)) {
			intersectionsX |= CollisionHandler::getIntersection(entity, collider->entity, Vector2D(positionChange.x, 0), Vector2D(0, 0));
		}
		for (auto& collider : Game::collisionHandler->getColliders(GroupLabel::COLLIDERS)) {
			intersectionsX |= CollisionHandler::getIntersection(entity, collider->entity, Vector2D(positionChange.x, 0), Vector2D(0, 0));
		}

		IntersectionBitSet intersectionsY = CollisionHandler::getIntersectionWithBounds(entity, positionChange);
		for (auto& collider : Game::collisionHandler->getColliders(GroupLabel::MAPTILES)) {
			intersectionsY |= CollisionHandler::getIntersection(entity, collider->entity, Vector2D(0, positionChange.y), Vector2D(0, 0));
		}
		for (auto& collider : Game::collisionHandler->getColliders(GroupLabel::COLLIDERS)) {
			intersectionsY |= CollisionHandler::getIntersection(entity, collider->entity, Vector2D(0, positionChange.y), Vector2D(0, 0));
		}

		if (this->entity->hasGroup((size_t) GroupLabel::PLAYERS) && this->entity->getTeam() == TeamLabel::BLUE)
			std::cout << intersectionsX << std::endl;

		if (intersectionsX.test((size_t) direction::LEFT) && positionChange.x < 0)
			positionChange.x = 0;

		if (intersectionsX.test((size_t) direction::RIGHT) && positionChange.x > 0)
			positionChange.x = 0;		

		if (intersectionsY.test((size_t) direction::UP) && positionChange.y < 0)
			positionChange.y = 0;

		if (intersectionsY.test((size_t) direction::DOWN) && positionChange.y > 0)
			positionChange.y = 0;
	}

	position += positionChange;
};