#pragma once

#include <array>
#include <memory>
#include <bitset>
#include <vector>

#include "ColliderComponent.h"
#include "ECS.h"
#include "Constants.h"

// TODO: remove here if possible
// temporary fix: addComponent function template doesnt know TransformComponent -> error undefined type
#include "InputComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class Manager;
class Component;

using ComponentBitSet = std::bitset<MAX_COMPONENTS>;
using GroupBitSet = std::bitset<MAX_GROUPS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;

/*!
 * 
 * \brief Main class for any object in game, stores associations, labeling and components
 * \details The entity class is the primary class each object in the game needs to use. Add components to assign functionality.
 *  
 * \todo More detailed description
 * \todo Some functions in entity class are only supposed to be called in specific context, which might be valid uses for `friend` keyword. Example: Entity() should only be called from Manager::addEntity(). Verify each functions intended use/scope.
 * 
 */
class Entity
{
public:

	/*! 
	 * \brief Used for rendering order (last is highest) or retrieving entities of group
	 * \todo Label used in singular entity shouldn't use plural
	 * \todo HEARTS are rendered above POWERUPS, missleading order
	 * \todo PROJECTILE are rendered above POWERUPS, missleading order
	 * \todo Generalize HEARTS as UI or similar
	 */
	enum class GroupLabel
	{
		MAPTILES, //!< Entity using TileComponent
		PLAYERS, //!< Primary entity in player controll
		ENEMIES, //!< \deprecated All players now grouped as Entity::PLAYERS
		COLLIDERS, //!< Fixed collider entity, e.g. a wall
	    PROJECTILE, //!< \todo Document
	    HEARTS, //!< \todo Document
	    POWERUPS //!< \todo Document
	};

	/*!
	 * \todo Document
	 */
	explicit Entity(Manager& mManager) :
		manager(mManager) { };

	void update(uint_fast16_t diffTime) const; //!< Call each frame to update all components

	bool isActive() const { return this->active; } //!< \sa destroy()
	//! Mark for destruction for Manager::refresh() and disables collision
	//! \sa ColliderComponent
	void destroy() {
		this->active = false;
		if (this->hasComponent<ColliderComponent>()) {
			this->getComponent<ColliderComponent>().removeCollision();
		}
	}

	bool hasGroup(Group mGroup); //!< \sa GroupLabel
	void addGroup(Group mGroup); //!< \sa GroupLabel
	void delGroup(Group mGroup); //!< \sa GroupLabel
	//! \returns bitset with true on position GroupLabel if the entity belongs to group
	//! \sa GroupLabel
	std::bitset<MAX_GROUPS> getGroupBitSet();

 	//! \sa Manager
	Manager& getManager() { return manager; };

	template <typename T> bool hasComponent() const //! \sa Component
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	//! \brief Adds specified type as component and calls Component::init() 
	//! \param mArgs Constructor arguments of component
	template <typename T, typename...TArgs> T& addComponent(TArgs&&...mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		this->components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	};
	
	template <typename T> T& getComponent() const //!< \todo: rewrite to use optionals
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray = {};
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;
};