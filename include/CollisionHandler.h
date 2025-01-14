#pragma once

//! \file CollisionHandler.h
//! \file CollisionHandler.cpp
//! \file TransformComponent.cpp

#include "ColliderComponent.h"
#include "Constants.h"
#include "Entity.h"
#include <SDL3/SDL_rect.h>
#include "SpriteComponent.h"
#include "Vector2D.h"
#include "Manager.h"

#include <bitset>
#include <initializer_list>
#include <tuple>
#include <utility>
#include <vector>

class ColliderComponent;
class Entity;

// [IntersectionBitSet]
constexpr uint8_t DIRECTION_C = 4;

using IntersectionBitSet = std::bitset<DIRECTION_C>;
// [IntersectionBitSet]

class CollisionHandler
{
private:
	Manager& manager;

public:

	CollisionHandler(Manager& mManager) :
		manager(mManager) { };
	~CollisionHandler();

	static IntersectionBitSet getIntersection( // intersections relative to entityA
		Entity* entityA,
		Entity* entityB,
		Vector2D posModA = Vector2D(0,0),
		Vector2D posModB = Vector2D(0,0));
	static IntersectionBitSet getIntersectionWithBounds( // will fail to determine direction if speed high enough to switch from no collision to full overlap in one tick
		Entity* entity,
		Vector2D posMod = Vector2D(0,0));

	// temporary function, remove once game.cpp cleaned up
	std::vector<ColliderComponent*> getColliders(
		std::initializer_list<Entity::GroupLabel> const& groupLabels,
		std::initializer_list<Entity*> const& excludedEntities = {});

	/*!
	 * 
	 * \brief Tests entity against all entities with the specified labels for a collision
	 * \details Tests the given entity against every other entity with the specified labels for intersections between their collison boxes.
	 * If the primary entity has no ColliderComponent, the equivalent of no collision is returned immediately, other entities are skipped
	 * if they don't have a ColliderComponent
	 * \param entity The primary entity to check against. Return values will be relative to this entity
	 * \param posMod Modifier to apply toposition before checking collisions.
	 * \param groupLabels Entities need to have at least one listed GroupLabels to get checked against
	 * \param teamLabels Entities need to have one of the specified TeamLabels to get checked against
	 * \param negateTeam If set to true, entities will only be checked against if they **don't** have one of the specified TeamLabels
	 * \see ColliderComponent
	 * 
	 */
	template<typename T>
	T getAnyIntersection(
		Entity* entity,
		Vector2D posMod = {},
		std::initializer_list<Entity::GroupLabel> const& groupLabels = {},
		std::initializer_list<Entity*> const& excludedEntities = {});

	void update();
};