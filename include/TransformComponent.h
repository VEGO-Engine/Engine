#pragma once
#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;

	int height = 32;
	int width = 32;
	int scale = 1;

	int speed = 3;


	TransformComponent()
	{
		position.zero();
	}

	TransformComponent(int scale)
	{
		position.zero();
		this->scale = scale;
	}

	TransformComponent(float x, float y)
	{
		this->position.x = x;
		this->position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, int scale)
	{
		this->position.x = x;
		this->position.y = y;
		this->width = w;
		this->height = h;
		this->scale = scale;
	}

	void init() override
	{
		velocity.zero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
