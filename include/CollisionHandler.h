#pragma once

#include "Constants.h"
#include "Entity.h"
#include "SDL_rect.h"
#include "SpriteComponent.h"
#include "Vector2D.h"
#include "Manager.h"

#include <bitset>
#include <initializer_list>
#include <vector>

class ColliderComponent;
class Entity;

constexpr uint8_t DIRECTION_C = 4;

enum class direction
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

using IntersectionBitSet = std::bitset<DIRECTION_C>;

class CollisionHandler
{
private:
	Manager& manager;

public:

	CollisionHandler(Manager& mManager) :
		manager(mManager) { };
	~CollisionHandler();


	static IntersectionBitSet getIntersection(Entity* entityA, Entity* entityB); // intersections relative to entityA
	static IntersectionBitSet getIntersection(Entity* entityA, Entity* entityB, Vector2D posModA, Vector2D posModB);
	static IntersectionBitSet getIntersectionWithBounds(Entity* entity);// will fail if speed high enough to switch from no collision to full overlap in one tick
	static IntersectionBitSet getIntersectionWithBounds(Entity* entity, Vector2D posMod);

	std::vector<ColliderComponent*> getColliders(std::initializer_list<GroupLabel> const& groupLabels); // temporary function, remove once game.cpp cleaned up

	void update();
};