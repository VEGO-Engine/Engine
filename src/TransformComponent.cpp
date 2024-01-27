#include "TransformComponent.h"
#include "Constants.h"

TransformComponent::TransformComponent()
{
	position.zero();
}

TransformComponent::TransformComponent(int scale)
{
	position.zero();
	this->scale = scale;
}

TransformComponent::TransformComponent(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

TransformComponent::TransformComponent(float x, float y, int scale)
{
	this->position.x = x;
	this->position.y = y;
	this->scale = scale;
}

TransformComponent::TransformComponent(float x, float y, int w, int h, int scale)
{
	this->position.x = x;
	this->position.y = y;
	this->width = w;
	this->height = h;
	this->scale = scale;
}

void TransformComponent::init()
{
	velocity.zero();
}

void TransformComponent::update()
{
	// if(velocity.x != 0 && velocity.y != 0)

	float multiplier = velocity.x != 0 && velocity.y != 0 ? 0.707 : 1; //normalizes vector

	Vector2D newPos(
		position.x + velocity.x * speed * multiplier,
		position.y + velocity.y * speed * multiplier
	);

	if (newPos.x < 0)
	{
		newPos.x = 0;
	}

	if (newPos.x + (this->width * this->scale) > SCREEN_SIZE_WIDTH)
	{
		newPos.x = SCREEN_SIZE_WIDTH - (this->width * this->scale);
	}

	if (newPos.y < 0)
	{
		newPos.y = 0;
	}

	if (newPos.y + (this->height * this->scale) > SCREEN_SIZE_HEIGHT)
	{
		newPos.y = SCREEN_SIZE_HEIGHT - (this->height * this->scale);
	}

	position = newPos;
}
