#include "Manager.h"

#include <algorithm>
#include <iterator>
#include <memory>
#include <numeric>
#include <ranges>
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
        [](const std::shared_ptr<Entity>& mEntity)
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
    entities.emplace_back(e);
    return *e;
}

void Manager::addExistingEntity(std::shared_ptr<Entity> entity)
{
    entities.emplace_back(entity);
    std::ranges::for_each(std::views::iota(0ul, MAX_GROUPS), [&entity, this](auto i) {
        if (entity->hasGroup(i)) {
            this->entitiesByGroup.at(i).emplace_back(entity.get());
        }
    });
}

std::shared_ptr<Entity> Manager::getShared(Entity* entity)
{
    auto entityPtr = std::find_if(std::begin(entities), std::end(entities), [&entity](const auto& entityPtr) {
        return entity == entityPtr.get();
    });
    return std::shared_ptr<Entity>(*entityPtr); // careful, error if find_if returns end
}

std::weak_ptr<Entity> Manager::getWeak(Entity* entity)
{
    auto entityPtr = std::find_if(std::begin(entities), std::end(entities), [&entity](const auto& entityPtr) {
        return entity == entityPtr.get();
    });
    return *entityPtr; // careful, error if find_if returns end
}