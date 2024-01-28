#include "CollisionHandler.h"

#include "ColliderComponent.h"
#include "Constants.h"
#include "Entity.h"
#include "Manager.h"
#include "Vector2D.h"

#include <SDL_rect.h>
#include <bitset>

IntersectionBitSet CollisionHandler::getIntersection(Entity* entityA, Entity* entityB) 
{
	return getIntersection(entityA, entityB, Vector2D(0,0), Vector2D(0,0));
}

IntersectionBitSet CollisionHandler::getIntersection(Entity* entityA, Entity* entityB, Vector2D posModA, Vector2D posModB)
{
	if (!entityA->hasComponent<ColliderComponent>() ||
		!entityB->hasComponent<ColliderComponent>())
		return std::bitset<DIRECTION_C>();

	SDL_Rect* colliderA = &entityA->getComponent<ColliderComponent>().collider;
	SDL_Rect* colliderB = &entityB->getComponent<ColliderComponent>().collider;

	if (!SDL_HasIntersection(
		colliderA,
		colliderB))
		return std::bitset<DIRECTION_C>();

	std::bitset<DIRECTION_C> intersections;

	// checks all 4 directions to allow checking full overlap
	if (colliderA->x + posModA.x < colliderB->x + colliderB->w + posModB.x)
		intersections.set((size_t) direction::LEFT) = 1;

	if (colliderA->x + colliderA->w + posModA.x > colliderB->x + posModB.x)
		intersections.set((size_t) direction::RIGHT) = 1;

	if (colliderA->y + posModA.y < colliderB->y + colliderB->h + posModB.y)
		intersections.set((size_t) direction::UP) = 1;

	if (colliderA->y + colliderA->h + posModA.y > colliderB->y + posModB.y)
		intersections.set((size_t) direction::DOWN) = 1;

	return intersections;
}

IntersectionBitSet CollisionHandler::getIntersectionWithBounds(Entity* entity) 
{
	return getIntersectionWithBounds(entity, Vector2D(0,0));
}

IntersectionBitSet CollisionHandler::getIntersectionWithBounds(Entity* entity, Vector2D posMod) 
{
	if (!entity->hasComponent<ColliderComponent>())
		return std::bitset<DIRECTION_C>();

	SDL_Rect* collider = &entity->getComponent<ColliderComponent>().collider;

	std::bitset<DIRECTION_C> intersections;

	// all 4 directions and both sides to allow checking for fully out of bounds
	if (collider->x + posMod.x < 0 ||
		collider->x + posMod.x > SCREEN_SIZE_WIDTH)
		intersections.set((size_t) direction::LEFT);

	if (collider->x + collider->w + posMod.x < 0 ||
		collider->x + collider->w + posMod.x > SCREEN_SIZE_WIDTH)
		intersections.set((size_t) direction::RIGHT);

	if (collider->y + posMod.y < 0 ||
		collider->y + posMod.y > SCREEN_SIZE_HEIGHT)
		intersections.set((size_t) direction::UP);

	if (collider->y + collider->h + posMod.y < 0 ||
		collider->y + collider->h + posMod.y > SCREEN_SIZE_HEIGHT)
		intersections.set((size_t) direction::DOWN);

	return intersections;
}

std::vector<ColliderComponent*> CollisionHandler::getColliders(GroupLabel groupLabel) 
{
	std::vector<ColliderComponent*> colliders;

	for (auto& entity : manager.getGroup((size_t) groupLabel)) {
		if (!entity->hasComponent<ColliderComponent>())
			continue;
		colliders.emplace_back(&entity->getComponent<ColliderComponent>());
	}

	return colliders;
}