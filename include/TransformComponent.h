#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Constants.h"
#include "DataComponent.h"

class TransformComponent : public Component
{
public:
	Vector2D position; // TODO: change to int to save CPU time -> possibly subpixel coordinates
	Vector2D direction;

	int height = 32;
	int width = 32;
	int scale = 1;

	explicit TransformComponent(int scale = 1);
	TransformComponent(float x, float y, int scale = 1);
	TransformComponent(float x, float y, int w, int h, int scale = 1);

	void init() override;
	void update() override;
	
	int getSpeed();

    void setPositionAfterCollision(Vector2D& positionChange);
};
