#pragma once

#include <array>
#include <memory>
#include <bitset>
#include <vector>

#include "ColliderComponent.h"
#include "ECS.h"
#include "Constants.h"

class Manager;
class Component;

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using GroupBitSet = std::bitset<MAX_GROUPS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

class Entity
{
public:

	/*! TODO */
	enum class GroupLabel
	{
		MAPTILES,
		PLAYERS,
		ENEMIES,
		COLLIDERS,
	    PROJECTILE,
	    HEARTS,
	    POWERUPS
	};

	enum class TeamLabel
	{
		NONE, //!< No team
		BLUE, //!< Team blue
		RED //!< Team red
	};

	explicit Entity(Manager& mManager) :
		manager(mManager) { };

	void update() const;
	void draw() const;

	bool isActive() const { return this->active; }
	void destroy() {
		this->active = false;
		if (this->hasComponent<ColliderComponent>()) {
			this->getComponent<ColliderComponent>().removeCollision();
		}
	}

	bool hasGroup(Group mGroup);
	void addGroup(Group mGroup);
	void delGroup(Group mGroup);
	std::bitset<MAX_GROUPS> getGroupBitSet();

	void setTeam(TeamLabel teamLabel);
	/*! TODO */
	TeamLabel getTeam();

	Manager& getManager() { return manager; };

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename...TArgs> T& addComponent(TArgs&&...mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		this->components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	};
	
	template <typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray = {};
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
	TeamLabel teamLabel;
};