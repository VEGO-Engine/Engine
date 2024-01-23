#pragma once

class Entity;

enum class GroupLabel
{
	MAP,
	PLAYERS,
	ENEMIES,
	COLLIDERS,
    PROJECTILE,
    HEARTS
};

class Component
{
public:
	Entity* entity;

	virtual void init()
	{
		// implementation in derived classes (when neccessary)
	}

	virtual void update()
	{
		// implementation in derived classes (when neccessary)
	}

	virtual void draw()
	{
		// implementation in derived classes (when neccessary)
	}

	virtual ~Component() = default;
};