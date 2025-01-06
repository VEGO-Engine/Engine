#include "Entity.h"

#include "Manager.h"
#include "Component.h"

#include "VEGO.h"

#include <cstddef>

void Entity::update(uint_fast16_t diffTime) const
{
	for (auto const& c : components) c->update(diffTime);
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

std::bitset<MAX_GROUPS> Entity::getGroupBitSet()
{
	return groupBitSet;
}

void Entity::destroy() {
    this->active = false;
    if (this->hasComponent<ColliderComponent>()) {
        this->getComponent<ColliderComponent>().removeCollision();
    }
    if (this->hasComponent<SpriteComponent>()) {
        VEGO_Game().renderManager.remove(&this->getComponent<SpriteComponent>());
    }
}

void Entity::reactivate() {
    this->active = true;
    if (this->hasComponent<ColliderComponent>()) {
        this->getComponent<ColliderComponent>().addCollision();
    }
    if (this->hasComponent<SpriteComponent>()) {
        VEGO_Game().renderManager.add(&this->getComponent<SpriteComponent>());
    }
}
