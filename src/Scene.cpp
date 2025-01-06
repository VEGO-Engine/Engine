#include "Scene.h"
#include "Entity.h"
#include "Map.h"
#include <algorithm>
#include <memory>
#include <ranges>
#include <vector>
#include <VEGO.h>

void Scene::addEntity(std::function<Entity*()> entityDefinition)
{
    this->entityFuncs.push_back(entityDefinition);

    if (this->active) {
        this->entities.emplace_back(VEGO_Game().manager.getWeak(entityDefinition()));
    }
}

void Scene::addTemporaryEntity(std::function<Entity*()> entityDefinition)
{
    if (this->active) {
        this->tempEntities.push_back(VEGO_Game().manager.getWeak(entityDefinition()));
        return;
    }

    this->tempEntityFuncs.push_back(entityDefinition);
}

void Scene::addInitFunc(std::function<void()> initFunc)
{
    this->initFuncs.push_back(initFunc);
}

void Scene::addUpdateFunc(std::function<void(uint_fast16_t diffTime)> updateFunc)
{
    this->updateFuncs.push_back(updateFunc);
}

void Scene::addResetFunc(std::function<void()> resetFunc)
{
    this->resetFuncs.push_back(resetFunc);
}

void Scene::init()
{
    this->map->generateTiles();

    std::ranges::for_each(this->initFuncs, [](const auto& func) {
        func();
    });
    std::ranges::for_each(this->entities, [](auto entity) {
        entity->reactivate();
        VEGO_Game().manager.addExistingEntity(entity);
    });
    std::ranges::for_each(this->entityFuncs, [this](const auto& func) {
        this->entities.emplace_back(VEGO_Game().manager.getShared(func()));
    });
    std::ranges::for_each(this->tempEntityFuncs, [this](const auto& func) {
        this->tempEntities.emplace_back(VEGO_Game().manager.getWeak(func()));
    });

    this->active = true;
}

void Scene::update(uint_fast16_t diffTime)
{
    std::ranges::for_each(this->updateFuncs, [diffTime](const auto& func) {
        func(diffTime);
    });
}

void Scene::reset()
{
    this->active = false;

    std::ranges::for_each(this->entities, [](const auto& entity) {
        entity->destroy();
    });
    std::ranges::for_each(this->tempEntities, [](const auto& entity) {
        if (!entity.expired())
        entity.lock()->destroy();
    });
    this->tempEntities.clear();
    std::ranges::for_each(this->resetFuncs, [](const auto& func) {
        func();
    });

    if (this->map) {
        this->map->removeTiles();
    }
}

void Scene::addMap(Map* map)
{
    this->map = map;
}

void Scene::addMap(const char* path)
{
    this->map_unique = std::unique_ptr<Map>(new Map(path));
    this->addMap(this->map_unique.get());
}