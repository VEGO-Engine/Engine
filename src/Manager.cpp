#include "Manager.h"

#include <algorithm>

#include "Constants.h"

void Manager::draw()
{
	for (auto& e : entities) e->draw();
}

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

	for (auto i(0u); i < MAX_TEAMS; i++)
	{
		auto& v(entitiesByTeam[i]);
		v.erase(
			std::remove_if(std::begin(v), std::end(v),
				[i](Entity* mEntity)
				{
					return !mEntity->isActive() || (size_t)(mEntity->getTeam()) != i;
				}), std::end(v));
	}

	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& mEntity)
		{
			return !mEntity->isActive();
		}),
		std::end(entities));
}

void Manager::update()
{
	for (auto& e : entities) e->update();
}

void Manager::addToGroup(Entity* mEntity, Group mGroup)
{
	entitiesByGroup[mGroup].emplace_back(mEntity);
}

std::vector<Entity*>& Manager::getGroup(Group mGroup)
{
	return entitiesByGroup[mGroup];
}

void Manager::addToTeam(Entity* mEntity, Team mTeam)
{
	entitiesByTeam[mTeam].emplace_back(mEntity);
}

std::vector<Entity*>& Manager::getTeam(Team mTeam)
{
	return entitiesByTeam[mTeam];
}

Entity& Manager::addEntity()
{
	Entity* e = new Entity(*this);
	std::unique_ptr<Entity> uPtr{ e };
	entities.emplace_back(std::move(uPtr));
	return *e;
}
