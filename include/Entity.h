#pragma once
#include <array>
#include <vector>
#include <bitset>
#include "Constants.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "ECS.h"

class Manager;

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using GroupBitSet = std::bitset<MAX_GROUPS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

class Entity
{
public:
	explicit Entity(Manager& mManager) : manager(mManager) { }

	void update() const;
	void draw() const;

	bool isActive() const { return this->active; }
	void destroy() { this->active = false; }

	bool hasGroup(Group mGroup);
	void addGroup(Group mGroup);
	void delGroup(Group mGroup);

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
};