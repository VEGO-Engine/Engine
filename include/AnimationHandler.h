#pragma once
#include <cstdint>
struct Animation
{
	uint8_t index;
	uint8_t frames;
	uint8_t speed;

	Animation() {}

	Animation(uint8_t index, uint8_t frames, uint8_t speed)
	{
		this->index = index;
		this->frames = frames;
		this->speed = speed;
	}
};

enum AnimationType //TODO enum class
{
	IDLE = 0,
	WALK = 1
};



