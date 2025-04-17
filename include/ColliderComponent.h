#pragma once

#include <SDL3/SDL.h>

#include "Component.h"
#include "Vector2D.h"

class TransformComponent;

//! \brief Adds a collision box to an entity when added via entity.addComponent()
class ColliderComponent : public Component
{
public:
	SDL_Rect& getCollider() { return collider; } //!< \returns the collider of the entity
	const char* getTag() const { return tag; } //!< \returns the tag of the entity
	bool hasCollision() const { return collision; } //!< \returns the collision state of the entity

	//! \brief Constructor for ColliderComponent
	//! \param tag The tag of the collider, can be any char*
	ColliderComponent(const char* tag);

	//! \brief Constructor for ColliderComponent
	//! \param tag The tag of the collider, can be any char*
	//! \param hitboxScale The scale of the collider, used to scale the collider size, default is 1.0f and takes up the 32x32 pixels
	ColliderComponent(const char* tag, float hitboxScale);

	void init() override;
	void update(uint_fast16_t diffTime) override;
	//! \brief Removes the collision of an entity
    void removeCollision();
private:
	SDL_Rect collider;
	const char* tag;
	TransformComponent* transform;
	bool collision; //added for removing collision of destroyed projectiles
	float hitboxScale; //adds a seperate variable for the scale of the hitbox (not the sprite) so each sprite can have a different hitbox size if needed
};