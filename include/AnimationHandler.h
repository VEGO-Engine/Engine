#pragma once

struct Animation
{
	int index;
	int frames;
	int speed;

	Animation() {}

	Animation(int i, int f, int s)
	{
		index = i;
		frames = f;
		speed = s;
	}
};

enum AnimationType
{
	IDLE = 0,
	WALK_R = 1,
	WALK_L = 2
};



