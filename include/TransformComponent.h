#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Constants.h"
#include "DataComponent.h"

//! \brief The transform component is responsible for the position, direction and size of an entity. It is used to move the entity in the game world and to determine its size and position on the screen.
class TransformComponent : public Component
{
public:
	Vector2D position; // TODO: change to int to save CPU time -> possibly subpixel coordinates

	//! \brief The direction in which the entity is moving. (0, 0) is the default and signifies no movement.
	//! \brief access direction with direction.x and direction.y for each direction
	//! \brief x = 1 for right, -1 for left
	//! \brief y = 1 for down, -1 for up
	Vector2D direction;

	int height = 32;
	int width = 32;
	float scale = 1;

	//! \attention in order to allow an entity to move the stat "speed" must be set in the DataComponent (written exactly like that and set to any positive int value, 0 will lead to no movement, negative numbers to backwards movement)

	//! \param scale base value is 1 (32x32px), size gets multiplied with scale
	explicit TransformComponent(float scale = 1);

	//! \param x x coordinate of spawnposition
	//! \param y y coordinate of spawnposition
	//! \param scale base value is 1 (32x32px per default), size gets multiplied with scale
	TransformComponent(float x, float y, float scale = 1);

	//! \param x x coordinate of spawnposition
	//! \param y y coordinate of spawnposition
	//! \param w add custom width
	//! \param h add custom height
	//! \param scale base value is 1 (32x32px per default), size gets multiplied with scale
	TransformComponent(float x, float y, int w, int h, float scale = 1);

	void init() override;
	void update(uint_fast16_t diffTime) override;
    void setPositionAfterCollision(Vector2D& positionChange);
	int getSpeed();

};
