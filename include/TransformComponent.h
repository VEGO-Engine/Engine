#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Constants.h"
#include "DataComponent.h"

//! \brief Adds a transform to an entity when added via entity.addComponent()
//! \details The transform component is responsible for the position, direction and size of an entity. It is used to move the entity in the game world and to determine its size and position on the screen.
class TransformComponent : public Component
{
public:
	Vector2D position; // TODO: change to int to save CPU time -> possibly subpixel coordinates
	Vector2D direction;

	int height = 32;
	int width = 32;
	int scale = 1;

	//! \attention in order to allow an entity to move the stat "speed" must be set in the DataComponent (written exactly like that and set to any positive int value, 0 will lead to no movement, negative numbers to backwards movement)
	explicit TransformComponent(int scale = 1);
	TransformComponent(float x, float y, int scale = 1);
	TransformComponent(float x, float y, int w, int h, int scale = 1);

	void init() override;
	void update(uint_fast16_t diffTime) override;
    void setPositionAfterCollision(Vector2D& positionChange);
	int getSpeed();

};
