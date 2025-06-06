#include "Manager.h"

#include <algorithm>
#include <vector>

#include "Constants.h"
#include "Entity.h"

void Manager::refresh()
{
	for (auto i(0u); i < MAX_GROUPS; i++)
	{
		auto& v(entitiesByGroup[i]);
		v.erase(
			std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
				{
					return !mEntity->isActive() || !mEntity->hasGroup(i);
				}), std::end(v));
	}

	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& mEntity)
		{
			return !mEntity->isActive();
		}),
		std::end(entities));
}

void Manager::update(uint_fast16_t diffTime)
{
	for (auto& e : entities) e->update(diffTime);
}

void Manager::addToGroup(Entity* mEntity, Group mGroup)
{
	entitiesByGroup.at(mGroup).emplace_back(mEntity);
}

std::vector<Entity*>& Manager::getGroup(Group mGroup)
{
	return entitiesByGroup.at(mGroup);
}

std::vector<Entity*> Manager::getAll()
{
	std::vector<Entity*> entity_vec;
	for (auto& entity_ptr : entities) {
		entity_vec.emplace_back(entity_ptr.get());
	}
	return entity_vec;
}

Entity& Manager::addEntity()
{
	Entity* e = new Entity(*this);
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	return *e;
}
