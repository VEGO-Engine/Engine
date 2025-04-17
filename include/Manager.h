#pragma once

#include <iostream>

#include <array>
#include <memory>
#include <vector>

#include "Constants.h"
#include "Entity.h"

class GameInternal;
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

#ifndef DOXYGEN_SHOULD_SKIP_THIS
	void addToGroup(Entity* mEntity, Group mGroup); //!< \todo `friend` to Entity
	std::vector<Entity*>& getGroup(Group mGroup); //!< \returns std::vector containing all entities in group Entity::GroupLabel
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

	//! \brief Returns all entities currently loaded in the game
	std::vector<Entity*> getAll(); //!< \returns std::vector containing all entities

	//! \brief Add a new entity to the game
	Entity& addEntity(); //!< Creates and returns a new, empty entity

	/// \deprecated Use \ref VEGO_Game() instead
	GameInternal* getGame() { return this->game; };

private:
	GameInternal* game;
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, MAX_GROUPS> entitiesByGroup;
};