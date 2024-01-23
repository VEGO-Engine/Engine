#pragma once
#include "Vector2D.h"
#include "Component.h"

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;

	TransformComponent();
	TransformComponent(int scale);
	TransformComponent(float x, float y);
	TransformComponent(float x, float y, int scale);
	TransformComponent(float x, float y, int w, int h, int scale);

	void init() override;
	void update() override;
};
