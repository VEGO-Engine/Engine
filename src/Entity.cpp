#include "Entity.h"

#include "Manager.h"
#include "Component.h"
#include <cstddef>

void Entity::update(uint_fast16_t diffTime) const
{
	for (auto const& c : components)
        if (c)
            c->update(diffTime);
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
