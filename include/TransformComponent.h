#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Constants.h"

class TransformComponent : public Component
{
public:
	Vector2D position; // TODO: change to int to safe CPU time -> possibly subpixel coordinates
	Vector2D direction;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent();
	explicit TransformComponent(int scale);
	TransformComponent(float x, float y);
	TransformComponent(float x, float y, int scale);
	TransformComponent(float x, float y, int w, int h, int scale);

	void init() override;
	void update() override;
	void modifySpeed(int8_t modifier);
};
