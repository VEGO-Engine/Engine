#pragma once
#include <iostream>
#include <array>
#include <memory>
#include <vector>

#include "Constants.h"
#include "Entity.h"

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
	void update(); //!< \sa Entity::update()
	void draw(); //!< \sa Entity::draw()
	//! Disables all functionality of entities marked for destruction  
	//! \sa Entity::destroy()
	void refresh();

	void addToGroup(Entity* mEntity, Group mGroup); //!< \todo `friend` to Entity
	std::vector<Entity*>& getGroup(Group mGroup); //!< \returns std::vector containing all entities in group Entity::GroupLabel

	void addToTeam(Entity* mEntity, Team mTeam); //!< \todo `friend` to Entity
	std::vector<Entity*>& getTeam(Team mTeam); //!< \returns std::vector containing all entities in team Entity::TeamLabel

	std::vector<Entity*> getAll(); //!< \returns std::vector containing all entities

	Entity& addEntity(); //!< Creates and returns a new, empty entity

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, MAX_GROUPS> entitiesByGroup;
	std::array<std::vector<Entity*>, MAX_TEAMS> entitiesByTeam;
};