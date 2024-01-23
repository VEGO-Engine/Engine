#pragma once
#include "Entity.h"
#include "Manager.h"
#include "Component.h"
//#include "ECS.h"

void Entity::update() const
{
	for (auto const& c : components) c->update();
}

void Entity::draw() const
{
	for (auto const& c : components) c->draw();
}

bool Entity::hasGroup(Group mGroup)
{
	return groupBitSet[mGroup];
}

void Entity::addGroup(Group mGroup)
{
	groupBitSet[mGroup] = true;
	manager.addToGroup(this, mGroup);
}

void Entity::delGroup(Group mGroup)
{
	groupBitSet[mGroup] = false;
}

//template <typename T> bool Entity::hasComponent() const
//{
//	return componentBitSet[getComponentTypeID<T>()];
//}

//template <typename T, typename...TArgs> T& Entity::addComponent(TArgs&&...mArgs)
//{
//	T* c(new T(std::forward<TArgs>(mArgs)...));
//	c->entity = this;
//	std::unique_ptr<Component> uPtr{ c };
//	this->components.emplace_back(std::move(uPtr));
//
//	componentArray[getComponentTypeID<T>()] = c;
//	componentBitSet[getComponentTypeID<T>()] = true;
//
//	c->init();
//	return *c;
//};

//template <typename T> T& Entity::getComponent() const
//{
//	auto ptr(componentArray[getComponentTypeID<T>()]);
//	return *static_cast<T*>(ptr);
//}