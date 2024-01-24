#include "TransformComponent.h"

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
	double multiplier = velocity.x != 0 && velocity.y != 0 ? 0.707 : 1; //normalizes vector
	position.x += velocity.x * speed * multiplier;
	position.y += velocity.y * speed * multiplier;
}