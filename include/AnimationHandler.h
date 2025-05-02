#pragma once
#include <cstdint>
//! \brief Animation struct to hold animation data
//! \param index The row in the sprite sheet (every 32 pixels on the y-axis is a new row)
//! \param frames The number of frames in the animation
//! \param speed The speed of the animation in milliseconds
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



