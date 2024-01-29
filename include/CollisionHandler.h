#pragma once

#include "ColliderComponent.h"
#include "Constants.h"
#include "Entity.h"
#include "SDL_rect.h"
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
		std::initializer_list<GroupLabel> const& groupLabels,
		std::initializer_list<TeamLabel> const& teamLabels = {},
		bool negateTeam = false);

	template<typename T>
	T getAnyIntersection(
		Entity* entity,
		Vector2D posMod = {},
		std::initializer_list<GroupLabel> const& groupLabels = {},
		std::initializer_list<TeamLabel> const& teamLabels = {},
		bool negateTeam = false);

	void update();
};