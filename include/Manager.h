#pragma once

#include <iostream>

#include <array>
#include <memory>
#include <vector>

#include "Constants.h"

class GameInternal;
class Entity;

/*!
 * 
 * \brief Is responsible for managing all entities
 * \details The manager class handles update and draw calls collectively for all entities, and provides functionality to get all or a subset of all entities
 * \sa Entity
 * \sa Entity::GroupLabel
 * \sa Entity::TeamLabel
 * 
 */
class Manager
{
public:
    Manager(GameInternal* game) : game(game) {};

    void update(uint_fast16_t diffTime); //!< \sa Entity::update()
    //! Disables all functionality of entities marked for destruction
    //! \sa Entity::destroy()
    void refresh();

    void addToGroup(Entity* mEntity, Group mGroup); //!< \todo `friend` to Entity
    std::vector<Entity*>& getGroup(Group mGroup); //!< \returns std::vector containing all entities in group Entity::GroupLabel

    std::vector<Entity*> getAll(); //!< \returns std::vector containing all entities

    Entity& addEntity(); //!< Creates and returns a new, empty entity

    GameInternal* getGame() { return this->game; };

    std::shared_ptr<Entity> getShared(Entity* entity);
    std::weak_ptr<Entity> getWeak(Entity* entity);

    // this function is ugly af and should not be merged
    void addExistingEntity(std::shared_ptr<Entity> entity);

private:
    GameInternal* game;
    std::vector<std::shared_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, MAX_GROUPS> entitiesByGroup;
};